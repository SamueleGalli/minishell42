/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:32:41 by sgalli            #+#    #+#             */
/*   Updated: 2023/10/09 15:31:23 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**new_tmp(t_env *e, char **tmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (e->env[j] != NULL)
	{
		tmp[i] = (char *)malloc(sizeof(char) * \
		(ft_strlen(e->env[j]) + 1));
		alloc_mat(tmp[i], e->env[j]);
		i++;
		j++;
	}
	tmp[i] = (char *)malloc(sizeof(char) * \
		(ft_strlen(e->v[e->i]) + 1));
	alloc_mat(tmp[i], e->v[e->i]);
	i++;
	tmp[i] = NULL;
	return (tmp);
}

void	apic_change(t_env *e, int i, char **tmp)
{
	int	j;

	j = 0;
	e->i--;
	e->indx = 0;
	tmp[i] = (char *)malloc(size(e) + 1);
	while (e->v[e->i][e->indx] != 0)
		tmp[i][j++] = e->v[e->i][e->indx++];
	if (e->v[e->i + 1] != NULL)
	{
		if (e->v[e->i + 1][0] == 34 || e->v[e->i + 1][0] == 39)
		{
			e->indx = 1;
			e->i++;
			while (e->v[e->i][e->indx] != 34 && e->v[e->i][e->indx] != 39
				&& e->v[e->i][e->indx] != 0)
				tmp[i][j++] = e->v[e->i][e->indx++];
		}
	}
	tmp[i][j] = '\0';
}

void	change_value(t_env *e, int i, char **tmp)
{
	if (e->v[e->i][0] == '\'' || e->v[e->i][0] == '\"')
		apic_change(e, i, tmp);
	else
	{
		tmp[i] = (char *)malloc(sizeof(char) * \
		(ft_strlen(e->v[e->i]) + 1));
		alloc_mat(tmp[i], e->v[e->i]);
	}
}
