/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd3.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:46:12 by sgalli            #+#    #+#             */
/*   Updated: 2024/03/22 10:46:20 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**copy_pwd(t_env *e, char **tmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (e->env[i] != NULL)
	{
		tmp[j] = (char *)malloc(sizeof(char) * (ft_strlen(e->env[i]) + 1));
		alloc_mat(tmp[j], e->env[i]);
		j++;
		i++;
	}
	tmp[j] = NULL;
	return (tmp);
}

void	update_pwd(t_env *e, int i, int j, char *p)
{
	int	t;

	t = 0;
	while (p[t] != 0)
	{
		e->env[i][j] = p[t];
		j++;
		t++;
	}
	e->env[i][j] = 0;
}

void	alloc_pwd(t_env *e, int i)
{
	char	p[1024];

	if (getcwd(p, 1024) != NULL)
	{
		e->env[i] = (char *)malloc(sizeof(char) * (ft_strlen(p) + \
		ft_strlen("PWD=") + 1));
		e->env[i][0] = 'P';
		e->env[i][1] = 'W';
		e->env[i][2] = 'D';
		e->env[i][3] = '=';
		update_pwd(e, i, 4, p);
	}
}
