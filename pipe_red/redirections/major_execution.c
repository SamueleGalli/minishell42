/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:45:48 by eraccane          #+#    #+#             */
/*   Updated: 2024/01/02 16:46:49 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execve_red(t_env *e, int fd)
{
	close(0);
	dup2(fd, 1);
	close(fd);
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
	exiting(e, 0);
}

void	fork_pid_zero(t_env *e, char *filename, int type)
{
	int	fd;

	if (type == 1)
		fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	else if (type == 2)
		fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0666);
	e->i = 0;
	if (fd < 0)
	{
		e->exit_code = 1;
		printf("bash: %s: No such file or directory\n", filename);
		exiting(e, 0);
	}
	execve_red(e, fd);
}

void	waiting2(t_env *e, pid_t pid)
{
	e->child = waitpid(pid, &e->status, 0);
	if (e->child == -1)
	{
		perror("waitpid");
		exiting(e, 1);
	}
	else
	{
		if (WIFEXITED(e->status) == 0)
			e->exit_code = 2;
		else
			e->exit_code = WEXITSTATUS(e->status);
	}
}

void	check_red_fork(t_env *e, char *filename, int type)
{
	pid_t	pid;

	e->s = NULL;
	if (check_builtin(e) == 0)
	{
		pathcmd(e);
		flag_matrix(e);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		e->exit = 1;
		exiting(e, 1);
	}
	else if (pid == 0)
		fork_pid_zero(e, filename, type);
	else
		waiting2(e, pid);
	e->exit = 1;
}
