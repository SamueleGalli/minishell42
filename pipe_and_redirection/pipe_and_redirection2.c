/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and_redirection2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:06:17 by sgalli            #+#    #+#             */
/*   Updated: 2023/11/10 18:13:15 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fork_loop_major(t_env *e)
{
	close(e->pipefd[1]);
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
			pipe_com(e);
		exiting(e, 0);
	}
	else
		variabletype(e);
	exiting(e, 0);
}

void	other_redir(t_env *e)
{
	int	i;

	i = e->i;
	e->define_pipe = 0;
	while (e->v[i] != NULL)
	{
		if (e->v[i][0] == '<' || e->v[i][0] == '>' || e->v[i][0] == '|')
		{
			if (e->v[i][0] == '|')
				e->define_pipe = 1;
			else if (e->v[i][0] == '<')
				e->define_pipe = 2;
			else if (e->v[i][0] == '>')
				e->define_pipe = 3;
			break ;
		}
		i++;
	}
}

void	fork_redir(t_env *e)
{
	e->pid_pipe = fork();
	if (e->pid_pipe < 0)
	{
		perror("fork");
		exiting(e, 1);
	}

}

void	pipe_single(t_env *e)
{
	close(e->pipefd[1]);
	dup2(e->pipefd[0], 0);
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
			pipe_com(e);
		exiting(e, 0);
	}
	else
		variabletype(e);
	exiting(e, 0);
}

void	define_redir(t_env *e)
{
	if (e->define_pipe == 0)
	{
		fork_redir(e);
		if (e->pid_pipe == 0)
			pipe_single(e);
		else
			parent_process(e);
	}
	else if (e->define_pipe == 1)
	{

		fork_redir(e);
		if (e->pid_pipe == 0)
			fork_loop_redir(e);
		else
			parent_process(e);
	}
	else if (e->define_pipe == 2 || e->define_pipe == 3)
	{
		fork_redir(e);
		if (e->pid_pipe == 0)
			fork_loop_major(e);
		else
			parent_process(e);
	}
}
