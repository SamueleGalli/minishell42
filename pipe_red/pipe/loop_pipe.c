/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:34:00 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/03 11:40:35 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cont_mult_pipe(t_env *e)
{
	e->pid_pipe = fork();
	if (e->pid_pipe < 0)
	{
		perror("fork");
		exiting(e, 1);
	}
	else if (e->pid_pipe == 0)
		fork_loop(e);
	else
		parent_loop_pipe(e);
}

void	multiple_pipe(t_env *e)
{
	signal(SIGINT, SIG_IGN);
	while (e->p_i < e->c_pipe + 1)
	{
		if (pipe(e->pipefd) == -1)
		{
			perror("pipe");
			exiting(e, 1);
		}
		cont_mult_pipe(e);
		e->p_i++;
		update_pipe(e);
	}
	while (waitpid(-1, &e->status, 0) > 0)
	{
	}
	if (WIFEXITED(e->status))
		e->exit_code = WEXITSTATUS(e->status);
	singals(e);
}
