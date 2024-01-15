/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   major_red.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 13:07:09 by eraccane          #+#    #+#             */
/*   Updated: 2024/01/15 12:08:13 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execve_red(t_env *e)
{
	e->i = e->tmp_i;
	if (check_builtin(e) == 0)
	{
		pathcmd(e);
		flag_matrix(e);
	}
	if (e->s != NULL)
	{
		if (e->c_path == 0 && access(e->s, X_OK) == 0 && check_builtin(e) == 0)
		{
			execve(e->s, e->mat_flag, e->env);
			perror("execve");
			exiting(e, 1);
		}
	}
	variabletype(e);
	after_file_exe(e);
	exiting(e, 0);
}

void	fork_pid_zero(t_env *e)
{
	int	fd;

	if (e->v[e->i][1] == '>')
		fd = loop_file(e, 0, 2);
	else
		fd = loop_file(e, 0, 1);
	if (e->filename != NULL)
		free(e->filename);
	close(0);
	dup2(fd, 1);
	close(fd);
	execve_red(e);
}

void	waiting2(t_env *e, pid_t pid)
{
	waitpid(pid, &e->status, 0);
	if (WIFEXITED(e->status) == 0)
		e->exit_code = 2;
	else
		e->exit_code = WEXITSTATUS(e->status);
}

void	check_red_fork(t_env *e)
{
	pid_t	pid;

	e->s = NULL;
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		e->exit = 1;
		exiting(e, 1);
	}
	else if (pid == 0)
		fork_pid_zero(e);
	else
		waiting2(e, pid);
	e->exit = 1;
}

void	redirect_mult_double(t_env *e)
{
	e->filename = find_filepath_major(e);
	if (e->exit_code == 0)
		check_red_fork(e);
	if (e->filename != NULL)
		free(e->filename);
}
