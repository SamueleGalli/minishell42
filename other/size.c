/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:22:39 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/02 16:30:04 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
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
