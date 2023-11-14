/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_in.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:44:15 by sgalli            #+#    #+#             */
/*   Updated: 2023/11/14 12:37:39 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//echo 42 < file1 | cat | wc -l

void	do_pipe_cont(t_env *e)
{
	if (e->v[e->i] == NULL)
		return ;
	while (e->v[e->i][0] != '|' && e->i != 0)
		e->i--;
	e->i++;
	if (check_builtin(e) == 1)
		e->valid = 1;
}

void	write_red(t_env *e)
{
	e->i = e->init_red;
	e->s = NULL;
	if (check_builtin(e) == 0)
	{
		pathcmd(e);
		flag_matrix(e);
	}
	if (e->s == NULL)
	{
		variabletype(e);
		close(e->fd_output);
		exiting(e, 1);
	}
	close(e->fd_output);
	execve(e->s, e->mat_flag, e->env);
	perror("execve");
	exiting(e, 1);
}

void	forking_in(t_env *e, char *fileoutput, int type)
{
	if (type == 1)
		e->fd_output = open(fileoutput, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	else if (type == 2)
		e->fd_output = open(fileoutput, O_WRONLY | O_APPEND | O_CREAT, 0666);
	free(fileoutput);
	if (e->fd_output < 0)
	{
		e->exit_code = 1;
		perror("open");
		return ;
	}
	dup2(e->fd_output, 1);
	write_red(e);
}

void	single_write(t_env *e, char *fileoutput, int type)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		e->exit = 1;
		exiting(e, 1);
	}
	if (pid == 0)
		forking_in(e, fileoutput, type);
	else
		waitpid(pid, NULL, 0);
}

void	last_in(t_env *e)
{
	char	*fileoutput;

	e->i = e->out_red;
	if (compare(e->v[e->out_red], ">>") == 1)
	{
		fileoutput = find_lasth_filepath(e);
		single_write(e, fileoutput, 2);
	}
	else
	{
		fileoutput = find_lasth_filepath(e);
		single_write(e, fileoutput, 1);
	}
	if (fileoutput != NULL)
		free(fileoutput);
	while (e->v[e->i] != NULL && e->v[e->i][0] != '|')
		e->i++;
}
