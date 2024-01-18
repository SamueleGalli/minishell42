/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cont_min_red.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:37:14 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/18 10:23:27 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	single_continuous(t_env *e, int fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		e->exit = 1;
		exiting(e, 1);
	}
	fork_cotinue(e, pid, fd);
}

void	print_in_pipe(t_env *e)
{
	close(e->pipefd[0]);
	dup2(e->pipefd[1], STDOUT_FILENO);
	close(e->pipefd[1]);
}

void	check_out(t_env *e)
{
	int	i;
	int	fd;

	fd = 0;
	i = e->i;
	e->filename = find_filepath_major(e);
	if (e->filename != NULL)
	{
		if (e->v[i][1] != '\0' && e->v[i][0] == '>')
			fd = open(e->filename, O_WRONLY | O_APPEND | O_CREAT, 0666);
		else
			fd = open(e->filename, O_WRONLY | O_TRUNC | O_CREAT, 0666);
		if (fd < 0)
		{
			perror("open");
			e->exit = 1;
			free(e->filename);
			exiting(e, 1);
		}
		free(e->filename);
		dup2(fd, STDOUT_FILENO);
		close (fd);
	}
	else
		free(e->filename);
}

void	fork_red_pipe(t_env *e, int fd)
{
	dup2(fd, STDIN_FILENO);
	close(fd);
	check_out(e);
	e->i = e->i_tmp;
	if (check_builtin(e) == 0)
	{
		if (e->output == -1 && e->input > -1 && e->piping == 1)
			print_in_pipe(e);
		pathcmd(e);
		flag_matrix(e);
		execve(e->s, e->mat_flag, e->env);
		perror("execve");
		exiting(e, e->exit_code);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	variabletype(e);
	exiting(e, e->exit_code);
}

void	fork_cotinue(t_env *e, pid_t pid, int fd)
{
	if (pid == 0)
		fork_red_pipe(e, fd);
	waitpid(pid, &e->status, 0);
	if (e->status != 0)
		e->exit_code = WEXITSTATUS(e->status);
	if (e->piping == 1)
	{
		close(e->pipefd[1]);
		dup2(e->pipefd[0], STDIN_FILENO);
		close(e->pipefd[0]);
	}
}
