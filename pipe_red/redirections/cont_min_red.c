/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cont_min_red.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:37:14 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/08 12:03:17 by sgalli           ###   ########.fr       */
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

void	fork_cotinue(t_env *e, pid_t pid, int fd)
{
	if (pid == 0)
	{
		e->i = e->i_tmp;
		dup2(fd, STDIN_FILENO);
		if (check_builtin(e) == 0)
		{
			pathcmd(e);
			flag_matrix(e);
			execve(e->s, e->mat_flag, e->env);
			perror("execve");
			exiting(e, 1);
		}
		variabletype(e);
		exiting(e, 0);
	}
	else
		waitpid(pid, &e->status, 0);
	if (e->status != 0)
		e->exit_code = WEXITSTATUS(e->status);
	close(fd);
}

void	single_major_redirect(t_env *e)
{
	char	*filename;
	int		fd;

	filename = find_filepath(e);
	if (compare(e->v[0], ">") == 1 || compare(e->v[0], "> ") == 1)
	{
		fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0666);
		if (fd < 0)
		{
			e->exit_code = 1;
			printf("bash: %s: No such file or directory\n", filename);
			exiting(e, 0);
		}
		close(fd);
	}
	else
		check_red_fork(e, filename, 1);
}

void	min_mult_redirect(t_env *e)
{
	int		fd;
	char	*filename;

	fd = 0;
	filename = NULL;
	if (prev_minor_red(e, fd, filename) == 0)
		return ;
	close(fd);
}
