/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 16:33:21 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/09 12:28:23 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pipe_red_start(t_env *e)
{
	while (e->v[e->i] != NULL)
	{
		do_pipe(e);
		e->piping = 0;
	}
	while (waitpid(-1, &e->status, 0) > 0)
	{
	}
	if (WIFEXITED(e->status) != 0)
		e->exit_code = WEXITSTATUS(e->status);
}

void	pipe_and_redirection(t_env *e)
{
	e->check_input = -1;
	e->in_red = 0;
	e->out_red = 0;
	e->pi_re = 1;
	if (exits_pipe(e) == 1)
		pipe_red_start(e);
	else
	{
		if (do_redir(e) == 0)
			return ;
	}
	dup2(e->stdin, STDIN_FILENO);
	close(e->stdin);
	dup2(e->stdout, STDOUT_FILENO);
	close(e->stdout);
	e->pi_re = 0;
	e->start_red = 0;
	e->i_tmp = 0;
}
