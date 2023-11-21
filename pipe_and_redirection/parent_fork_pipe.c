/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_fork_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:04:52 by sgalli            #+#    #+#             */
/*   Updated: 2023/11/21 13:36:47 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipe_loop_redir(t_env *e)
{
	if (check_builtin(e) == 0 && e->p_i == 0 && e->i != 0 && e->tmp_i == 0)
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
	//if (e->p_i == 0)
	dup2(e->pipefd[0], STDIN_FILENO);
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
	waitpid(e->pid_pipe, &e->status, 0);
	if (WIFEXITED(e->status) != 0)
		e->exit_code = 0;
}
