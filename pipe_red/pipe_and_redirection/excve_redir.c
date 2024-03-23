/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excve_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 09:34:08 by sgalli            #+#    #+#             */
/*   Updated: 2024/03/23 12:55:39 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exec_red(t_env *e)
{
	e->s = NULL;
	if (check_builtin(e) == 0)
		exiting(e, 0);
	if (e->s == NULL)
	{
		variabletype(e);
		exiting(e, 1);
	}
	perror("execve");
	exiting(e, 1);
}

void	pid_red(t_env *e, char *file)
{
	int	fd;

	if (e->v[e->check + 1][0] == '>' && e->v[e->check + 1][1] == '>')
		fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0666);
	else
		fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (fd == -1)
	{
		printf("bash: %s: No such file or directory\n", file);
		exiting(e, 1);
	}
	if (file != NULL)
		free(file);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	exec_red(e);
}

void	execve_redir(t_env *e)
{
	char	*file;
	pid_t	pid;

	file = find_lasth_filepath(e);
	e->i = e->check + 1;
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exiting(e, 1);
	}
	if (pid == 0)
		pid_red(e, file);
	else
	{
		singal_fork(e);
		waitpid(pid, NULL, 0);
	}
	if (file != NULL)
		free(file);
	e->do_redir = 0;
}
