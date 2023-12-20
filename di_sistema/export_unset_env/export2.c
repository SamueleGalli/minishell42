/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:59:12 by sgalli            #+#    #+#             */
/*   Updated: 2023/12/20 12:12:38 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	apice_dimension(t_env *e, int k)
{
	int	i;
	int	c;

	c = 0;
	i = e->i + 1;
	k++;
	while (e->v[i][k] && e->v[i][k] != '\'' && e->v[i][k] != '\"')
	{
		k++;
		c++;
	}
	return (c);
}

void	update_env_v(t_env *e, int k, int i, char **tmp)
{
	int	apice;

	apice = 0;
	if (e->v[e->i + 1] != 0 && (e->v[e->i + 1][0] == '\'' || \
	e->v[e->i + 1][0] == '\"'))
		apice = apice_dimension(e, k);
	tmp[i] = (char *)malloc(sizeof(char) * (ft_strlen(e->v[e->i]) + apice + 1));
	apice = 0;
	while (e->v[e->i][k])
		tmp[i][apice++] = e->v[e->i][k++];
	if (e->v[e->i + 1] && (e->v[e->i + 1][0] == '\'' || \
	e->v[e->i + 1][0] == '\"'))
	{
		k = 1;
		while (e->v[e->i + 1][k] && e->v[e->i + 1][k] != '\'' && \
		e->v[e->i + 1][k] != '\"')
			tmp[i][apice++] = e->v[e->i + 1][k++];
	}
	tmp[i][apice] = '\0';
}

void	check_similar(t_env *e)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (e->env[i] != NULL)
	{
		while (e->env[i][j] && e->v[e->i][j] && \
		e->env[i][j] != '=' && e->v[e->i][j] != '=' && \
		e->env[i][j] == e->v[e->i][j])
			j++;
		if (e->env[i][j] == '=')
		{
			e->count_exp = i;
			return ;
		}
		j = 0;
		i++;
	}
}

void	new_export(t_env *e)
{
	char	**tmp;

	e->r = 0;
	check_similar(e);
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

void	cont_espfun(t_env *e)
{
	if (e->v[e->i + 1] != 0 && (e->v[e->i + 1][0] == 34 \
	|| e->v[e->i + 1][0] == 39))
	{
		new_export(e);
		e->i += 2;
	}
	else
	{
		new_export(e);
		e->i++;
	}
}
