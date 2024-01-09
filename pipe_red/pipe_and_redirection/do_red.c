/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_red.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 11:25:35 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/09 12:41:27 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_last_check(t_env *e)
{
	if (e->v[e->i] == NULL)
	{
		e->i = e->check;
		return ;
	}
	else if (e->v[e->i][0] == '|')
		e->i = e->check;
	else if (e->v[e->i][0] == '>')
	{
		e->i = e->check + 1;
		e->do_redir = 1;
	}
	else
	{
		e->i = e->check;
		e->i++;
		e->i_tmp = e->i;
	}
}

void	initialize_red(t_env *e)
{
	e->in_red = 0;
	e->check_input = -1;
	e->out_red = 0;
}

int	do_redir(t_env *e)
{
	initialize_red(e);
	while (e->v[e->i] != NULL && e->v[e->i][0] != '|')
	{
		while (e->v[e->i][0] != '<' && e->v[e->i][0] != '>')
			e->i++;
		red_type(e);
		if (e->do_redir == 1)
			execve_redir(e);
		if (update_redir(e) == 0)
			return (0);
		e->i_tmp = e->i;
		if (e->v[e->i] != NULL && e->v[e->i][0] == '|')
			e->i_tmp++;
	}
	if (e->in_red > 0 && e->out_red > 0)
		last_file(e);
	return (1);
}
