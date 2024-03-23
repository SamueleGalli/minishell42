/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 10:50:39 by sgalli            #+#    #+#             */
/*   Updated: 2024/03/23 12:29:58 by sgalli           ###   ########.fr       */
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
		cont_check_dimension(e);
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
	if (e->cmd[e->j] == '>' || e->cmd[e->j] == '<' || e->cmd[e->j] == '|')
		splong_red(e);
	else if (e->cmd[e->j] == 39 || e->cmd[e->j] == 34)
	{
		split_clousure(e);
		e->iter++;
	}
	else
	{
		while (e->cmd[e->j] != 0 && e->cmd[e->j] != ' ' && \
		e->cmd[e->j] != '|' && e->cmd[e->j] != '<' && \
		e->cmd[e->j] != '>')
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
	if (e->v[e->i][e->lenght - 1] == 0)
		return ;
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
		else if (e->cmd[e->indx] == '|' || e->cmd[e->indx] == '<' || \
		e->cmd[e->indx] == '>')
			check_red_other(e);
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
	e->q_null = 0;
	e->numb = spacer(e);
	e->v = (char **)malloc(sizeof(char *) * (e->numb + 1));
	if (e->v == NULL)
		exiting(e, 0);
	e->i = 0;
	e->indx = 0;
	cont_splitme(e);
}
