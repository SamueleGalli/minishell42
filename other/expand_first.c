/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_first.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 09:55:43 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/18 13:19:50 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_len_exp(t_env *e, int j, int i)
{
	int	len;

	len = 0;
	e->j = j;
	while (e->env[j][i] != '=')
		i++;
	i++;
	while (e->env[j][i] != 0)
	{
		if (e->env[j][i] == ' ')
			i++;
		else if (e->env[j][i] != 0 && e->env[j][i] != ' ')
		{
			e->i2 = i;
			len++;
			while (e->env[j][i] != 0 && e->env[j][i] != ' ')
				i++;
		}
	}
	return (len);
}

int	check_expanding(t_env *e, int j, int i)
{
	int	i2;

	i2 = 1;
	while (e->env[j] != NULL)
	{
		while (e->v[0][i2] == e->env[j][i] && e->v[0][i2] != 0
			&& e->env[j][i] != '=')
		{
			i2++;
			i++;
		}
		if (e->env[j][i] == '=')
			return (count_len_exp(e, j, i));
		else
		{
			i2 = 1;
			i = 0;
		}
		j++;
	}
	return (0);
}

void	update_v(t_env *e)
{
	free_table(e->v);
	e->v = NULL;
	e->v = (char **)malloc(sizeof(char *) * (size_mat(e->t)));
	while (e->t[e->i] != NULL)
	{
		e->v[e->i] = (char *)malloc(sizeof(char) * (ft_strlen(e->t[e->i]) + 1));
		alloc_mat(e->v[e->i], e->t[e->i]);
		e->i++;
	}
	e->v[e->i] = NULL;
	free_table(e->t);
	e->i = 0;
}

void	nulling_v(t_env *e)
{
	free_table(e->v);
	e->v[0] = NULL;
}

void	expand_first(t_env *e)
{
	int	i;
	int	c;

	i = size_mat(e->v) - 2;
	i += check_expanding(e, 0, 0);
	if (i == 0)
	{
		nulling_v(e);
		return ;
	}
	e->t = (char **)malloc(sizeof(char *) * (i + 1));
	c = alloc_str(e, 0, 0);
	i = 1;
	while (e->v[i] != NULL)
	{
		e->t[c] = (char *)malloc(sizeof(char) * (ft_strlen(e->v[i]) + 1));
		alloc_mat(e->t[c], e->v[i]);
		c++;
		i++;
	}
	e->t[c] = NULL;
	update_v(e);
	e->i = 0;
}
