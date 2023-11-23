/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe_or_redirection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 16:33:21 by sgalli            #+#    #+#             */
/*   Updated: 2023/11/22 12:28:23 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_type(t_env *e)
{
	if (e->v[e->i] == NULL)
		return (0);
	else if (e->v[e->i][0] == '<')
	{
		e->start_red = e->check;
		e->input = e->check;
		return (1);
	}
	else if (e->v[e->i][0] == '|')
	{
		e->i = e->check;
		e->check = 0;
		return (2);
	}
	else if (e->v[e->i][0] == '>')
	{
		e->start_red = e->check;
		e->output = e->check;
		return (1);
	}
	return (0);
}

int	pipe_or_redir(t_env *e)
{
	e->output = -1;
	e->input = -1;
	e->check = e->i;
	while (e->v[e->i] != NULL && e->v[e->i][0] != '|' && e->v[e->i][0] != '<' \
	&& e->v[e->i][0] != '>')
		e->i++;
	return (check_type(e));
}

void	pipe_and_redirection(t_env *e)
{
	e->check_input = -1;
	e->in_red = 0;
	e->out_red = 0;
	while (e->v[e->i] != NULL)
	{
		if (pipe_or_redir(e) == 1)
		{
			if (do_redir(e) == 0)
				return ;
		}
		else
			do_pipe(e);
	}
	dup2(e->stdin, STDIN_FILENO);
	close(e->stdin);
	dup2(e->stdout, STDOUT_FILENO);
	close(e->stdout);
	e->start_red = 0;
}
