/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:06:25 by sgalli            #+#    #+#             */
/*   Updated: 2023/11/08 19:11:36 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// if (e->cmd[i] == '<' || e->cmd[i] == '>')
//     return (0);
// printf("e->cmd: (i-1)-> |%c|, (i)-> |%c|\n\n", e->cmd[i - 1], e->cmd[i]);

int	split_pipe(t_env *e)
{
	int	i;

	if (e->cmd[e->j + 1] != 0 && e->cmd[e->j] != '\0' && e->cmd[e->j] == ' '
		&& e->cmd[e->iter] == ' ')
	{
		i = e->j;
		while (e->cmd[i] != '\0' && e->cmd[i] != '>' && e->cmd[i] != '<')
			i++;
		if (e->cmd[i] == '>' || e->cmd[i] == '<')
			return (0);
		return (1);
	}
	else
		return (0);
}

void	word(t_env *e)
{
	if (e->cmd[e->indx] == '$')
		e->indx++;
	e->word++;
	while (e->cmd[e->indx] != ' ' && e->cmd[e->indx] != 0
		&& e->cmd[e->indx] != 39 && e->cmd[e->indx] != 34
		&& e->cmd[e->indx] != '$')
	{
		e->indx++;
	}
}

void	quote_check(t_env *e)
{
	if (e->cmd[e->indx + 1] == 0)
	{
		e->indx++;
		return ;
	}
	if (e->cmd[e->indx + 1] != '\0' && e->cmd[e->indx + 1] != e->cmd[e->indx])
	{
		e->word++;
		e->indx++;
		while (e->cmd[e->indx] != 39 && e->cmd[e->indx] != 34
			&& e->cmd[e->indx] != 0)
			e->indx++;
		if (e->cmd[e->indx] == '\0')
			return ;
		e->indx++;
	}
	else
		e->indx += 2;
}

void	writing_split(t_env *e)
{
	if (e->cmd[e->indx] == 39 || e->cmd[e->indx] == 34)
	{
		e->v[e->i][e->lenght++] = e->cmd[e->indx++];
		while (e->cmd[e->indx] != 0 && e->cmd[e->indx] != 39
			&& e->cmd[e->indx] != 34)
			e->v[e->i][e->lenght++] = e->cmd[e->indx++];
		if (e->count == 1)
			e->v[e->i][e->lenght++] = ' ';
		e->v[e->i][e->lenght++] = e->cmd[e->indx++];
	}
	else
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
}

void	cont_splitme(t_env *e)
{
	while (e->i < e->numb && e->cmd[e->indx] != 0)
	{
		while (e->cmd[e->indx] == ' ')
			e->indx++;
		if (e->cmd[e->indx] == '\0')
			break ;
		if ((e->cmd[e->indx] == 39 || e->cmd[e->indx] == 34) && e->cmd[e->indx \
			+ 1] == e->cmd[e->indx])
			e->indx += 2;
		else
		{
			split(e);
			e->i++;
		}
	}
	e->v[e->i] = NULL;
}
