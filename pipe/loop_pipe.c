/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:34:00 by sgalli            #+#    #+#             */
/*   Updated: 2023/11/10 17:04:32 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	{
		close(e->pipefd[1]);
		dup2(e->pipefd[0], STDIN_FILENO);
		close(e->pipefd[0]);
		waitpid(e->pid_pipe, &e->status, 0);
		if (WIFEXITED(e->status))
			e->exit_code = WEXITSTATUS(e->status);
	}
}

void	multiple_pipe(t_env *e)
{
	while (e->p_i < e->c_pipe)
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
	parent2(e);
}
