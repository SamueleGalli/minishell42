/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 10:56:05 by sgalli            #+#    #+#             */
/*   Updated: 2024/03/25 17:58:18 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// grep hi "<infile" <         ./test_files/infile

#include "../minishell.h"

void	split_clousure(t_env *e)
{
	int	j2;

	j2 = e->j;
	e->j++;
	e->word++;
	if (e->cmd[e->j - 1] == 39 || e->cmd[e->j - 1] == 34)
	{
		while (e->cmd[e->j] != 0)
		{
			if (e->cmd[e->j] == e->cmd[j2] && (e->cmd[e->j + 1] == 0
					|| e->cmd[e->j + 1] == ' '))
				break ;
			else if (check_quote_sindoub(e) == 1)
				e->j = e->j + 2;
			if (e->cmd[e->j] != e->cmd[j2])
				e->word++;
			e->j++;
		}
		e->word++;
	}
}

void	alloc_quote(t_env *e)
{
	int	i;
	int	i2;

	i2 = e->indx;
	i = e->lenght;
	e->v[e->i][e->lenght++] = e->cmd[e->indx++];
	if (e->v[e->i][i] == 39 || e->v[e->i][i] == 34)
	{
		while (e->cmd[e->indx] != 0)
		{
			if (e->cmd[e->indx] == e->cmd[i2] && (e->cmd[e->indx + 1] == 0
					|| e->cmd[e->indx + 1] == ' '))
				break ;
			else if ((e->cmd[e->indx] == '\'' || e->cmd[e->indx] == '\"')
				&& (e->cmd[e->indx + 1] == e->cmd[e->indx]))
				e->indx += 2;
			else
				e->v[e->i][e->lenght++] = e->cmd[e->indx++];
		}
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

void	write_null(t_env *e)
{
	int	j;

	j = e->indx - 1;
	e->indx += 2;
	if (e->q_null == 0)
	{
		e->v[e->i] = (char *)malloc(sizeof(char) * 3);
		e->v[e->i][0] = e->cmd[j];
		e->v[e->i][1] = e->cmd[j];
		e->v[e->i][2] = 0;
		e->i++;
		e->q_null = 1;
		return ;
	}
	e->v[e->i] = (char *)malloc(sizeof(char) * 2);
	e->v[e->i][0] = ' ';
	e->v[e->i][1] = 0;
	e->i++;
}
