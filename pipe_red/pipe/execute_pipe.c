/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:06:17 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/25 11:41:27 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	father_pipe(t_env *e)
{
	execve(e->s, e->mat_flag, e->env);
	perror("execve");
	exiting(e, 1);
}

void	child_do_pipe(t_env *e)
{
	close(e->pipefd[0]);
	if (which_pipe(e) == 0)
		dup2(e->pipefd[1], STDOUT_FILENO);
	close(e->pipefd[1]);
	if (e->no_here == 1)
		exiting(e, e->exit_code);
	if (check_builtin(e) == 0)
	{
		pathcmd(e);
		flag_matrix(e);
	}
	else
		e->s = NULL;
	if (e->s != NULL)
	{
		if (e->c_path == 0 && access(e->s, X_OK) == 0)
			father_pipe(e);
	}
	else
		variabletype(e);
	exiting(e, e->exit_code);
}

void	execute_pipe(t_env *e)
{
	e->pid_pipe = fork();
	if (e->pid_pipe < 0)
	{
		perror("fork");
		exiting(e, 1);
	}
	if (e->pid_pipe == 0)
		child_do_pipe(e);
	else
	{
		close(e->pipefd[1]);
		dup2(e->pipefd[0], STDIN_FILENO);
		close(e->pipefd[0]);
	}
}
