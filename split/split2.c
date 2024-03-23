/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:06:25 by sgalli            #+#    #+#             */
/*   Updated: 2024/03/23 12:30:32 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	while (e->cmd[e->indx] != ' ' && e->cmd[e->indx] != 0 \
		&& e->cmd[e->indx] != '|' && e->cmd[e->indx] != '<' \
		&& e->cmd[e->indx] != '>')
		e->indx++;
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
		while (e->cmd[e->indx] != 0)
		{
			if ((e->cmd[e->indx] == 34 || e->cmd[e->indx] == 39) && \
			e->cmd[e->indx + 1] == ' ')
				break ;
			e->indx++;
		}
		if (e->cmd[e->indx] == '\0')
			return ;
		e->indx++;
	}
	else
		check_next_car(e);
}

void	writing_split(t_env *e)
{
	if (e->cmd[e->indx] == 39 || e->cmd[e->indx] == 34)
		alloc_quote(e);
	else if (e->cmd[e->indx] == '|' || e->cmd[e->indx] == '<' || \
	e->cmd[e->indx] == '>')
		write_redir(e);
	else
	{
		if (e->cmd[e->indx] == '$')
			e->v[e->i][e->lenght++] = e->cmd[e->indx++];
		while (e->cmd[e->indx] != ' ' && e->cmd[e->indx] != 0
			&& e->cmd[e->indx] != '|' && e->cmd[e->indx] != '<' \
			&& e->cmd[e->indx] != '>')
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
		else if ((e->cmd[e->indx] == 39 || \
		e->cmd[e->indx] == 34) && e->cmd[e->indx \
			+ 1] == e->cmd[e->indx])
			write_null(e);
		else
		{
			split(e);
			e->i++;
		}
	}
	e->v[e->i] = NULL;
}
