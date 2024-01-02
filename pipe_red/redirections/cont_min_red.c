/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cont_min_red.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:34:56 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/02 16:55:24 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	single_continuous(t_env *e, int fd)
{
	pid_t	pid;

	e->i = 0;
	if (check_builtin(e) == 0)
	{
		pathcmd(e);
		flag_matrix(e);
	}
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
		dup2(fd, STDIN_FILENO);
		close(fd);
		variabletype(e);
		exiting(e, 0);
	}
	else
		waitpid(pid, NULL, 0);
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

void	single_minor_redirect(t_env *e)
{
	int		fd;
	char	*filename;

	fd = 0;
	filename = NULL;
	if (prev_minor_red(e, fd, filename) == 0)
		return ;
	if (e->v[0][0] != '<' && e->v[0][0] != '>')
		single_continuous(e, fd);
	e->exit = 1;
	close(fd);
}

void	min_mult_redirect(t_env *e)
{
	int		fd;
	char	*filename;

	e->in_red = e->i;
	filename = find_filepath_minor_mult(e);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		e->exit_code = 1;
		e->exit = 1;
		printf("bash: %s: No such file or directory\n", filename);
		free(filename);
		e->true_red = 1;
		return ;
	}
	free(filename);
	close(fd);
}
