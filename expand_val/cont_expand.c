/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cont_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 11:18:14 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/19 11:53:39 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_val(t_env *e, int j, int i, int c)
{
	int	len;

	e->j = j;
	e->i2 = ++i;
	len = ((size_mat(e->v) - 1) + count_len_exp(e, j, 0, 0));
	e->t = (char **)malloc(sizeof(char *) * len);
	while (e->v[c] != NULL && e->v[c][0] != '$')
	{
		e->t[c] = (char *)malloc(sizeof(char) * (ft_strlen(e->v[c]) + 1));
		alloc_mat(e->t[c], e->v[c]);
		c++;
	}
	c = alloc_str(e, 0, c);
	e->t[c] = NULL;
	e->i = 0;
	update_v(e);
	e->i = 1;
}

int	is_empty_variable(t_env *e, int j, int i)
{
	int	i2;

	i2 = 1;
	while (e->env[j] != NULL)
	{
		while (e->v[e->i][i2] == e->env[j][i] && e->v[e->i][i2] != 0
			&& e->env[j][i] != '=')
		{
			i2++;
			i++;
		}
		if (e->env[j][i] == '=')
		{
			expand_val(e, j, i, 0);
			return (1);
		}
		else
		{
			i2 = 1;
			i = 0;
		}
		j++;
	}
	return (0);
}
