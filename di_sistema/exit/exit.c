/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:07:19 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/02 16:21:38 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_max_min(t_env *e)
{
	if (e->v[e->i + 1] != NULL)
	{
		if (ft_strlen(e->v[e->i + 1]) == 19 && e->v[e->i + 1][18] >= '8')
		{
			printf("bash: exit: %s: numeric argument required\n", e->v[e->i
				+ 1]);
			exiting(e, 2);
		}
		else if (ft_strlen(e->v[e->i + 1]) == 20 && e->v[e->i + 1][19] > '8')
		{
			printf("bash: exit: %s: numeric argument required\n", e->v[e->i
				+ 1]);
			exiting(e, 2);
		}
	}
}

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
