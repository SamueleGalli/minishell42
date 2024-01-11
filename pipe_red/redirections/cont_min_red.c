/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cont_min_red.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:37:14 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/11 11:57:13 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	min_mult_redirect(t_env *e)
{
	int		fd;
	char	*filename;

	fd = 0;
	filename = NULL;
	if (prev_minor_red(e, fd, filename) == 0)
		return ;
}

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

void	fork_red_pipe(t_env *e, int fd)
{
	e->i = e->i_tmp;
	dup2(fd, STDIN_FILENO);
	close(fd);
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
	e->n_fork++;
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
