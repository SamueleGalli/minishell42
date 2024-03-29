/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:36:35 by sgalli            #+#    #+#             */
/*   Updated: 2024/03/25 18:22:47 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	size_env(t_env *e)
{
	int	size;
	int	i3;

	i3 = e->i2;
	size = 0;
	while (e->env[e->j][e->i2] != 0 && e->env[e->j][e->i2] != ' ')
	{
		size++;
		e->i2++;
	}
	e->i2 = i3;
	return (size);
}

int	size(t_env *e)
{
	e->indx = 0;
	e->count = 0;
	while (e->v[e->i][e->indx] != 0)
	{
		e->count++;
		e->indx++;
	}
	if (e->v[e->i + 1] != NULL)
	{
		if (e->v[e->i + 1][0] == 34 || e->v[e->i + 1][0] == 39)
		{
			e->i++;
			e->indx = 1;
			while (e->v[e->i][e->indx] != 34 && \
			e->v[e->i][e->indx] != 39 && e->v[e->i][e->indx] != 0)
			{
				e->count++;
				e->indx++;
			}
			e->i--;
		}
	}
	e->indx = 0;
	return (e->count);
}

int	size_mat(char **t)
{
	int	i;

	i = 0;
	while (t[i] != NULL)
		i++;
	return (i + 1);
}

int	ft_strlen_red(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (s == NULL)
		return (0);
	if (s[i] == 34 || s[i] == 39)
		i++;
	while (s[i] != '\0' && s[i] != 34 && s[i] != 39)
	{
		j++;
		i++;
	}
	return (j);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}
