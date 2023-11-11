/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 10:50:39 by sgalli            #+#    #+#             */
/*   Updated: 2023/11/06 18:23:37 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	check_dimension(t_env *e)
{
	e->j = e->indx - 1;
	e->iter = e->indx;
	if (e->cmd[e->iter] == 39 || e->cmd[e->iter] == 34)
	{
		e->iter++;
		while (e->cmd[e->iter] != 34 && e->cmd[e->iter] != 39
			&& e->cmd[e->iter] != 0)
			e->iter++;
		if (e->cmd[e->iter] == '\0')
			return (0);
		e->iter++;
	}
	else
	{
		while (e->cmd[e->iter] != ' ' && e->cmd[e->iter] != 0
			&& e->cmd[e->iter] != 39 && e->cmd[e->iter] != 34)
			e->iter++;
	}
	return (split_pipe(e));
}

int	splong(t_env *e)
{
	e->j = e->indx;
	e->word = 0;
	if (e->cmd[e->j] == 39 || e->cmd[e->j] == 34)
	{
		e->j++;
		e->word++;
		while (e->cmd[e->j] != 39 && e->cmd[e->j] != 34 && e->cmd[e->j] != 0)
		{
			e->word++;
			e->j++;
		}
		e->word++;
	}
	else
	{
		while (e->cmd[e->j] != 0 && e->cmd[e->j] != ' ')
		{
			e->word++;
			e->j++;
		}
	}
	return (e->word);
}

void	split(t_env *e)
{
	e->count = 0;
	e->lenght = splong(e);
	if (e->i > 0 && e->space == 0)
		e->count = check_dimension(e);
	e->v[e->i] = malloc(sizeof(char) * e->lenght + 1 + e->count);
	if (e->v[e->i] == NULL)
		return ;
	e->lenght = 0;
	writing_split(e);
	e->v[e->i][e->lenght] = 0;
}

int	spacer(t_env *e)
{
	while (e->cmd[e->indx] != 0)
	{
		while (e->cmd[e->indx] == ' ')
			e->indx++;
		if (e->cmd[e->indx] != 0 && (e->cmd[e->indx] == 34
				|| e->cmd[e->indx] == 39))
			quote_check(e);
		else
			word(e);
	}
	return (e->word);
}

void	splitme(t_env *e)
{
	check_built(e->cmd, 0, e);
	e->indx = 0;
	e->word = 0;
	e->numb = spacer(e);
	e->v = (char **)malloc(sizeof(char *) * (e->numb + 1));
	if (e->v == NULL)
		exiting(e, 0);
	e->i = 0;
	e->indx = 0;
	cont_splitme(e);
}
