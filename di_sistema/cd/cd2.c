/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 09:51:17 by sgalli            #+#    #+#             */
/*   Updated: 2024/03/22 10:46:11 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	len_env(t_env *e, int i)
{
	int	j;
	int	k;

	k = 0;
	j = e->expand;
	while (e->env[i][j] != 0)
	{
		if (e->env[i][j] == ' ')
			j++;
		else
		{
			k++;
			j++;
		}
	}
	return (k);
}

void	expand(t_env *e, int i)
{
	char	*tmp;
	int		l;

	l = 0;
	l = len_env(e, i);
	tmp = (char *)malloc(sizeof(char) * (l + 1));
	l = 0;
	while (e->env[i][e->expand] != 0)
	{
		if (e->env[i][e->expand] == ' ')
			e->expand++;
		else
			tmp[l++] = e->env[i][e->expand++];
	}
	tmp[l] = 0;
	tilde_or_not(e, tmp);
	free(tmp);
}

void	go_tilde(t_env *e, int i, int j)
{
	char	*tmp;
	int		i2;

	i2 = 0;
	tmp = malloc(sizeof(char) * (len_tilde(e->env[i], j) + 1));
	while (e->env[i][j] != '\0')
		tmp[i2++] = e->env[i][j++];
	tmp[i2] = '\0';
	if (chdir(tmp) == -1)
	{
		e->exit = 1;
		e->exit_code = 1;
		printf("bash: cd: %s: No such file or directory\n", tmp);
	}
	free(tmp);
}

void	cont_pwd(t_env *e)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = (char **)malloc(sizeof(char *) * (size_mat(e->env) + 1));
	tmp = copy_pwd(e, tmp);
	free_table(e->env);
	e->env = (char **)malloc(sizeof(char *) * (size_mat(tmp)));
	while (tmp[i] != 0)
	{
		if (tmp[i] != 0 && tmp[i][0] == 'P' && tmp[i][1] == 'W' \
		&& tmp[i][2] == 'D' && tmp[i][3] == '=')
			alloc_pwd(e, i);
		else
		{
			e->env[i] = (char *)malloc(sizeof(char) * (ft_strlen(tmp[i]) + 1));
			alloc_mat(e->env[i], tmp[i]);
		}
		i++;
	}
	free_table(tmp);
	e->env[i] = NULL;
}

void	go_root(t_env *e, int i)
{
	while (e->env[i] != NULL)
	{
		if (e->env[i][0] == 'H' && e->env[i][1] == 'O' && e->env[i][2] == 'M'
			&& e->env[i][3] == 'E')
		{
			go_tilde(e, i, 5);
			return ;
		}
		i++;
	}
}
