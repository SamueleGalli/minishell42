/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd3.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:46:12 by sgalli            #+#    #+#             */
/*   Updated: 2024/03/25 17:31:28 by sgalli           ###   ########.fr       */
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
	if (e->pwd == 0)
	{
		tmp[j] = (char *)malloc(sizeof(char) * (ft_strlen("OLDPWD=") + 1));
		alloc_mat(tmp[j], "OLDPWD=");
		j++;
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
		e->env[i] = (char *)malloc(sizeof(char) * (ft_strlen(p)
					+ ft_strlen("PWD=") + 1));
		e->env[i][0] = 'P';
		e->env[i][1] = 'W';
		e->env[i][2] = 'D';
		e->env[i][3] = '=';
		update_pwd(e, i, 4, p);
	}
}

void	alloc_old_pwd(t_env *e, int i)
{
	int	j;
	int	t;

	t = 7;
	j = 0;
	e->env[i] = (char *)malloc(sizeof(char) * (ft_strlen(e->tmp_pwd)
				+ ft_strlen("OLDPWD=") + 1));
	e->env[i][0] = 'O';
	e->env[i][1] = 'L';
	e->env[i][2] = 'D';
	e->env[i][3] = 'P';
	e->env[i][4] = 'W';
	e->env[i][5] = 'D';
	e->env[i][6] = '=';
	while (e->tmp_pwd[j] != 0)
		e->env[i][t++] = e->tmp_pwd[j++];
	e->env[i][t] = 0;
	free(e->tmp_pwd);
	e->tmp_pwd = 0;
}

int	while_pwd(t_env *e, int i, char **tmp)
{
	while (tmp[i] != 0)
	{
		if (tmp[i] != 0 && tmp[i][0] == 'P' && tmp[i][1] == 'W'
			&& tmp[i][2] == 'D' && tmp[i][3] == '=')
		{
			alloc_pwd(e, i);
		}
		else if (tmp[i] != 0 && tmp[i][0] == 'O' && tmp[i][1] == 'L'
			&& tmp[i][2] == 'D' && tmp[i][3] == 'P' && tmp[i][4] == 'W'
			&& tmp[i][5] == 'D' && tmp[i][6] == '=')
			alloc_old_pwd(e, i);
		else
		{
			e->env[i] = (char *)malloc(sizeof(char) * (ft_strlen(tmp[i]) + 1));
			alloc_mat(e->env[i], tmp[i]);
		}
		i++;
	}
	return (i);
}
