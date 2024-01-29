/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_red.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 11:25:35 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/29 10:54:26 by sgalli           ###   ########.fr       */
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

int	do_redir(t_env *e)
{
	e->check_input = -1;
	while (e->v[e->i] != NULL && e->v[e->i][0] != '|')
	{
		while (e->v[e->i][0] != '<' && e->v[e->i][0] != '>')
			e->i++;
		redirect_mult_single(e);
		if (e->here != 0 && e->v[e->i] != NULL && \
		e->v[e->i][0] != '|' && e->v[e->i][0] != '>' \
		&& e->v[e->i][0] != '<')
			variabletype(e);
		if (e->do_redir == 1)
			execve_redir(e);
		if (update_redir(e) == 0)
			return (0);
		e->i_tmp = e->i;
		if (e->v[e->i] != NULL && e->v[e->i][0] == '|')
			e->i_tmp++;
	}
	return (1);
}
