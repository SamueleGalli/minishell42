/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:32:57 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/15 10:08:10 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	envionment(t_env *e)
{
	int	i;

	i = 0;
	while (e->env[i] != NULL)
	{
		printf("%s\n", e->env[i]);
		i++;
	}
	return ;
}

void	update_env(t_env *e)
{
	char	**tmp;

	tmp = (char **)malloc(sizeof(char *) * (size_mat(e->env) + 1));
	tmp = exclude_env(e, tmp);
	free_table(e->env);
	e->env = (char **)malloc(sizeof(char *) * (size_mat(tmp)));
	e->r = 0;
	while (tmp[e->r] != NULL)
	{
		e->env[e->r] = (char *)malloc(sizeof(char) * \
		(ft_strlen(tmp[e->r]) + 1));
		alloc_mat(e->env[e->r], tmp[e->r]);
		e->r++;
	}
	e->env[e->r] = NULL;
	free_table(tmp);
}

void	check_env(t_env *e)
{
	e->i++;
	e->r = 0;
	e->indx = 0;
	while (e->env[e->r] != NULL && e->v[e->i] != 0)
	{
		while (e->env[e->r][e->indx] != 0 && e->v[e->i][e->indx] != 0 \
		&& e->env[e->r][e->indx] == e->v[e->i][e->indx])
			e->indx++;
		if (e->env[e->r][e->indx] == '=')
		{
			update_env(e);
			e->r = 0;
			e->indx = 0;
			e->i++;
		}
		else
		{
			e->r++;
			e->indx = 0;
		}
	}
}
