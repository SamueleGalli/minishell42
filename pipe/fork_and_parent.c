/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_and_parent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 12:17:38 by sgalli            #+#    #+#             */
/*   Updated: 2023/11/10 18:41:34 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parent2(t_env *e)
{
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
	close(e->pipefd[0]);
	close(e->pipefd[1]);
	dup2(e->stdout, STDOUT_FILENO);
	close(e->stdout);
	dup2(e->stdin, STDIN_FILENO);
	close(e->stdin);
}

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

void	fork_loop(t_env *e)
{
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

void	parent_process(t_env *e)
{
	if (e->define_pipe == 0 || e->define_pipe == 2 || e->define_pipe == 3)
	{
		close(e->pipefd[1]);
		close(e->pipefd[0]);
	}
	else
	{
		close(e->pipefd[1]);
		dup2(e->pipefd[0], STDIN_FILENO);
		close(e->pipefd[0]);
	}
	if (e->define_pipe == 1 && e->p_i == 0)
		return ;
	waitpid(e->pid_pipe, &e->status, 0);
	if (WIFEXITED(e->status) != 0)
	{
		// e->exit = 1;
		e->exit_code = 1;
	}
}
