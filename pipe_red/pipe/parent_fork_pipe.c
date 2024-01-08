/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_fork_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:04:52 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/05 10:26:38 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	father_com(t_env *e)
{
	e->pid = fork();
	if (e->pid < 0)
	{
		e->exit = 1;
		perror("fork");
		exiting(e, 1);
	}
	else if (e->pid == 0)
	{
		execve(e->s, e->mat_flag, e->env);
		e->exit = 1;
		perror("execve");
		exiting(e, 1);
	}
	waitpid(e->pid, NULL, 0);
}

void	pipe_loop_redir(t_env *e)
{
	if (check_builtin(e) == 0 && e->i == 0 && e->i != 0 && e->tmp_i == 0)
	{
		close(e->pipefd[0]);
		close(e->pipefd[1]);
		exiting(e, 0);
	}
	close(e->pipefd[0]);
	dup2(e->pipefd[1], STDOUT_FILENO);
	close(e->pipefd[1]);
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
			pipe_com(e);
		exiting(e, 0);
	}
	else
		variabletype(e);
	exiting(e, 0);
}

void	parent_pipe_red(t_env *e)
{
	close(e->pipefd[1]);
	close(e->pipefd[0]);
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
			father_com(e);
	}
	else
		variabletype(e);
}

void	parent_process(t_env *e)
{
	close(e->pipefd[1]);
	dup2(e->pipefd[0], STDIN_FILENO);
	close(e->pipefd[0]);
}
