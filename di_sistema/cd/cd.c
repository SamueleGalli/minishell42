/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:28:41 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/03 11:41:18 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

	if (e->v[e->i + 1][1] == '?')
	{
		printf("bash: cd: %d: No such file or directory\n", e->exit_code);
		return ;
	}
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

int	len_tilde(char *s, int i)
{
	while (s[i] != 0)
		i++;
	return (i);
}

void	tilde_or_not(t_env *e, char *tmp)
{
	if (tmp[0] == '~')
	{
		go_root(e, 0);
		return ;
	}
	else if (chdir(tmp) == -1)
	{
		e->exit_code = 1;
		e->exit = 1;
		printf("bash: cd: %s: No such file or directory\n", tmp);
	}
}
