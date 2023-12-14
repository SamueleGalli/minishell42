/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:28:41 by sgalli            #+#    #+#             */
/*   Updated: 2023/12/14 10:12:43 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*format(char *s)
{
	char	*tmp;
	int		j;
	int		i;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			j++;
		}
		i++;
	}
	tmp = (char *)malloc(sizeof(char) * (j + 1));
	j = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] >= '0' && s[i] <= '9')
			tmp[j++] = s[i];
		i++;
	}
	tmp[j] = 0;
	return (tmp);
}

void	cont_what_exit(t_env *e)
{
	char	*s;
	int		i;

	i = 0;
	if (e->v[e->i + 1] == NULL)
		return ;
	if ((e->v[e->i + 1][i] == '-' || e->v[e->i + 1][i] == '+') && e->v[e->i
		+ 1][i + 1] == 0)
	{
		if (e->v[e->i + 1][0] == '-')
			e->sign = -1;
		else
			e->sign = 1;
		e->i++;
		if (e->v[e->i + 1] == NULL)
			return ;
	}
	s = format(e->v[e->i + 1]);
	if (e->sign == -1)
		e->exit_code = 256 - ft_atoi(s);
	else if (e->sign == 1)
		e->exit_code = ft_atoi(s);
	free(s);
	exiting(e, e->exit_code);
}

int	expanding_cd_dollar(t_env *e, int i, int j)
{
	while (e->env[i][j] != 0 && e->env[i][j] != ' ')
		j++;
	if (e->env[i][j] == 0)
		return (1);
	else
		while (e->env[i][j] != 0 && e->env[i][j] == ' ')
			j++;
	if (e->env[i][j] == 0)
		return (1);
	else
		return (0);
}

int	cont_cd_dollar(t_env *e, int i, int j)
{
	e->expand = j + 1;
	if (e->env[i + 1] != NULL)
		i++;
	while (e->env[i][j] != 0 && e->env[i][j] == ' ')
		j++;
	while (e->env[i][j] != 0 && e->env[i][j] != ' ')
		j++;
	if (e->env[i][j] == ' ')
	{
		while (e->env[i][j] != 0 && e->env[i][j] == ' ')
			j++;
		if (expanding_cd_dollar(e, i, j) == 1)
			expand(e, i);
		else
		{
			e->exit_code = 1;
			printf("bash: cd: too many arguments\n");
			return (1);
		}
	}
	else if (e->env[i][j] == 0)
		expand(e, i);
	return (1);
}

void	cd_dollar(t_env *e, int i, int j)
{
	int	s;

	while (e->env[i])
	{
		s = j + 1;
		while (e->v[e->i + 1][s] != 0 && e->env[i][j] != 0
			&& e->env[i][j] == e->v[e->i + 1][s])
		{
			s++;
			j++;
		}
		if (e->env[i][j] != 0 && e->env[i][j] == '=' && (e->v[e->i + 1][s] == 0
				|| e->v[e->i + 1][s] == ' '))
			if (cont_cd_dollar(e, i, j) == 1)
				return ;
		i++;
		j = 0;
	}
}
