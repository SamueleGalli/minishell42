/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:59:12 by sgalli            #+#    #+#             */
/*   Updated: 2023/12/14 11:17:12 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	continuing_check(t_env *e, int i, int j, int j2)
{
	if (e->v[e->i][j] == ' ' && e->env[i][j2] == '\0')
		e->equal = 1;
	if (e->v[e->i][j] == ' ' && e->env[i][j2] == ' ')
	{
		e->equal = 1;
		return ;
	}
	if (e->v[e->i][j] == 34 || e->v[e->i][j] == 39)
		j++;
	while (e->env[i][j2] == e->v[e->i][j] && e->v[e->i][j] != 0
		&& e->env[i][j2] != 0)
	{
		j2++;
		j++;
	}
	if (e->v[e->i][j] == 34 || e->v[e->i][j] == 39)
		j++;
	if (e->v[e->i][j] == 0 && e->env[i][j2] == 0)
		e->equal = 1;
	else
	{
		e->ex = i;
		e->equal = 2;
	}
}

void	check_export(t_env *e, int i, int j)
{
	while (e->env[i] != NULL)
	{
		while (e->env[i][j] == e->v[e->i][j] && e->v[e->i][j] != '='
			&& e->env[i][j] != '=')
			j++;
		if (e->env[i][j] == '=' && e->v[e->i][j] == '=')
		{
			j++;
			if (e->v[e->i][j] == 0 && e->v[e->i + 1] != NULL)
			{
				e->i++;
				continuing_check(e, i, 0, j);
			}
			else
				continuing_check(e, i, j, j);
		}
		j = 0;
		i++;
	}
}

void	not_equal(t_env *e)
{
	char	**tmp;

	tmp = (char **)malloc(sizeof(char *) * size_mat(e->env));
	tmp = alloc_tmp(e, tmp);
	free_table(e->env);
	e->env = (char **)malloc(sizeof(char *) * (size_mat(tmp) + 1));
	while (tmp[e->r] != NULL)
	{
		e->env[e->r] = (char *)malloc(sizeof(char) * (ft_strlen(tmp[e->r])
					+ 1));
		alloc_mat(e->env[e->r], tmp[e->r]);
		e->r++;
	}
	e->env[e->r] = NULL;
	free_table(tmp);
}

void	new_export(t_env *e)
{
	char	**tmp;

	e->r = 0;
	if (e->equal == 1)
		return ;
	else if (e->equal == 2)
		not_equal(e);
	else
	{
		tmp = (char **)malloc(sizeof(char *) * (size_mat(e->env) + 1));
		tmp = new_tmp(e, tmp);
		free_table(e->env);
		e->env = (char **)malloc(sizeof(char *) * size_mat(tmp));
		while (tmp[e->r] != NULL)
		{
			e->env[e->r] = (char *)malloc(sizeof(char) * (ft_strlen(tmp[e->r])
						+ 1));
			alloc_mat(e->env[e->r], tmp[e->r]);
			e->r++;
		}
		free_table(tmp);
		e->env[e->r] = NULL;
	}
}

void	cont_espfun(t_env *e)
{
	if (e->v[e->i + 1] != 0)
	{
		if (e->v[e->i + 1][0] == 34 || e->v[e->i + 1][0] == 39)
		{
			check_export(e, 0, 0);
			if (e->env != NULL)
				new_export(e);
			e->i += 2;
		}
		else
		{
			check_export(e, 0, 0);
			if (e->env != NULL)
				new_export(e);
			e->i++;
		}
	}
	else
	{
		check_export(e, 0, 0);
		if (e->env != NULL)
			new_export(e);
		e->i++;
	}
}
