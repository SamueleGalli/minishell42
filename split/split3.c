/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 10:56:05 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/03 11:43:53 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	split_clousure(t_env *e)
{
	e->j++;
	e->word++;
	if (e->cmd[e->j - 1] == 39)
	{
		while (e->cmd[e->j] != 0 && e->cmd[e->j] != 39)
		{
			e->word++;
			e->j++;
		}
		e->word++;
	}
	else if (e->cmd[e->j - 1] == 34)
	{
		while (e->cmd[e->j] != 0 && e->cmd[e->j] != 34)
		{
			e->word++;
			e->j++;
		}
		e->word++;
	}
}

void	alloc_quote(t_env *e)
{
	int	i;

	i = e->lenght;
	e->v[e->i][e->lenght++] = e->cmd[e->indx++];
	if (e->v[e->i][i] == 39)
	{
		while (e->cmd[e->indx] != 0 && e->cmd[e->indx] != 39)
			e->v[e->i][e->lenght++] = e->cmd[e->indx++];
	}
	else
	{
		while (e->cmd[e->indx] != 0 && e->cmd[e->indx] != 34)
			e->v[e->i][e->lenght++] = e->cmd[e->indx++];
	}
	if (e->count == 1)
		e->v[e->i][e->lenght++] = ' ';
	e->v[e->i][e->lenght++] = e->cmd[e->indx++];
}

void	cont_check_dimension(t_env *e)
{
	int	i;

	i = e->iter;
	e->iter++;
	if (e->cmd[i] == 39)
	{
		while (e->cmd[e->iter] != 0 && e->cmd[e->iter] != 39)
			e->iter++;
	}
	else
	{
		while (e->cmd[e->iter] != 0 && e->cmd[e->iter] != 34)
			e->iter++;
	}
}

void	expand_variable(t_env *e)
{
	if (e->cmd[e->indx] == '$')
		e->v[e->i][e->lenght++] = e->cmd[e->indx++];
	while (e->cmd[e->indx] != ' ' && e->cmd[e->indx] != 0
		&& e->cmd[e->indx] != 39 && e->cmd[e->indx] != 34
		&& e->cmd[e->indx] != '$')
		e->v[e->i][e->lenght++] = e->cmd[e->indx++];
	if (e->cmd[e->indx] == 34 || e->cmd[e->indx] == 39)
		if (e->cmd[e->indx + 1] == '\0')
			e->v[e->i][e->lenght++] = e->cmd[e->indx++];
	if (e->count == 1)
		e->v[e->i][e->lenght++] = ' ';
}
