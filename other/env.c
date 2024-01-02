/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 12:23:00 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/02 15:54:17 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	copy_env(t_env *e, char **env)
{
	int	i;

	i = 0;
	e->env = (char **)malloc(sizeof(char *) * size_mat(env));
	while (env[i] != NULL)
	{
		if (env[i][0] == 'P' && env[i][1] == 'A')
		{
			e->path = (char *)malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
			alloc_mat(e->path, env[i]);
		}
		e->env[i] = (char *)malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
		alloc_mat(e->env[i], env[i]);
		i++;
	}
	e->env[i] = NULL;
}

char	**exclude_env(t_env *e, char **tmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (e->env[i] != NULL)
	{
		if (i == e->r)
			i++;
		if (e->env[i] == NULL)
			break ;
		tmp[j] = (char *)malloc(sizeof(char) * (ft_strlen(e->env[i]) + 1));
		alloc_mat(tmp[j], e->env[i]);
		j++;
		i++;
	}
	tmp[j] = NULL;
	return (tmp);
}
