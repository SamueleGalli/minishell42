/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 10:37:55 by sgalli            #+#    #+#             */
/*   Updated: 2023/11/03 17:34:31 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exporapice(t_env *e, int i, int j)
{
	if (e->v[i + 1] != NULL)
	{
		if (e->v[i + 1][0] == 34 || e->v[i + 1][0] == 39)
		{
			i++;
			j++;
			while (e->v[i][j] != '\0')
			{
				if (e->v[i][j] == 34 || e->v[i][j] == 39)
				{
					if (e->v[i][0] == e->v[i][j])
						return (0);
				}
				j++;
			}
			return (1);
		}
	}
	return (0);
}

void	shortwhile(t_env *e)
{
	while (e->v[e->i][e->indx] != 0)
		e->env[e->r][e->iter++] = e->v[e->i][e->indx++];
	if (e->v[e->i + 1] != NULL)
	{
		if (e->v[e->i + 1][0] == 34 || e->v[e->i + 1][0] == 39)
		{
			e->indx = 1;
			e->i++;
			while (e->v[e->i][e->indx] != 34 && e->v[e->i][e->indx] != 39
				&& e->v[e->i][e->indx] != 0)
				e->env[e->r][e->iter++] = e->v[e->i][e->indx++];
		}
	}
	e->env[e->r][e->iter] = '\0';
	e->env[++e->r] = NULL;
}

int	valid_element(t_env *e, int i, int j)
{
	if (e->v[i][j] >= '0' && e->v[i][j] <= '9')
		return (1);
	else
		return (0);
}

int	exporterror(t_env *e, int i, int j)
{
	while (e->v[i][j] != 0)
		j++;
	if (e->v[i][j - 1] != '=')
	{
		j = 0;
		while (e->v[i][j] != 0)
		{
			if (e->v[i][j] == '=')
			{
				while (e->v[i][j] != 0)
					j++;
				if (e->v[i][j - 1] == 34 || e->v[i][j - 1] == 39)
					return (1);
				else
					return (0);
			}
			j++;
		}
		return (1);
	}
	j = 0;
	return (exporapice(e, i, j));
}

void	espfun(t_env *e)
{
	if (e->v[e->i][0] == ' ')
		return ;
	if (exporterror(e, 1, 0) == 1 || valid_element(e, 1, 0) == 1)
	{
		e->exit = 1;
		printf("invalid element\n");
		return ;
	}
	e->indx = 0;
	e->iter = 0;
	e->i = 1;
	e->equal = 0;
	check_export(e, 0, 0);
	if (e->env != NULL)
		new_export(e);
}
