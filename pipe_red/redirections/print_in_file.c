/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_red.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:57:03 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/02 16:32:46 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	read_and_write(t_env *e)
{
	e->i = e->start_red;
	if (e->v[e->i][0] == '>' || e->v[e->i][0] == '<')
		e->i--;
	e->s = NULL;
	if (check_builtin(e) == 0)
	{
		pathcmd(e);
		flag_matrix(e);
	}
	if (e->s == NULL)
	{
		variabletype(e);
		exiting(e, 1);
	}
	execve(e->s, e->mat_flag, e->env);
	perror("execve");
	exiting(e, 1);
}

void	forking_red(t_env *e, char *fileoutput, int type, char *fileinput)
{
	int	fdin;
	int	fdout;

	fdin = open(fileinput, O_RDONLY);
	free(fileinput);
	if (type == 1)
		fdout = open(fileoutput, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	else if (type == 2)
		fdout = open(fileoutput, O_WRONLY | O_APPEND | O_CREAT, 0666);
	free(fileoutput);
	if (fdout < 0 || fdin < 0)
	{
		perror("open");
		exiting(e, 1);
		return ;
	}
	dup2(fdout, 1);
	close(fdout);
	dup2(fdin, 0);
	close(fdin);
	read_and_write(e);
}

void	writing(t_env *e, char *fileoutput, int type, char *fileinput)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exiting(e, 1);
		exiting(e, 1);
	}
	if (pid == 0)
		forking_red(e, fileoutput, type, fileinput);
	else if (pid > 0)
	{
		waitpid(pid, &e->status, 0);
		if (WIFEXITED(e->status) != 0)
			e->exit_code = 1;
	}
}

void	last_file(t_env *e)
{
	char	*fileinput;
	char	*fileoutput;

	e->i = e->in_red;
	fileinput = find_filepath_minor_mult(e);
	e->i = e->out_red;
	if (compare(e->v[e->out_red], ">>") == 1)
	{
		fileoutput = find_lasth_filepath(e);
		writing(e, fileoutput, 2, fileinput);
	}
	else
	{
		fileoutput = find_lasth_filepath(e);
		writing(e, fileoutput, 1, fileinput);
	}
	if (fileinput != NULL)
		free(fileinput);
	if (fileoutput != NULL)
		free(fileoutput);
	while (e->v[e->i] != NULL && e->v[e->i][0] != '|')
		e->i++;
}
