/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_red.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:57:03 by sgalli            #+#    #+#             */
/*   Updated: 2023/11/10 16:48:35 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	read_and_write(int fdin, int fdout, t_env *e)
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
		close(fdin);
		close(fdout);
		exiting(e, 1);
	}
	close(fdout);
	close(fdin);
	execve(e->s, e->mat_flag, e->env);
	perror("execve");
	exiting(e, 1);
}

void	forking_red(t_env *e, char *fileoutput, int type, char *fileinput)
{
	int	fdin;

	fdin = open(fileinput, O_RDONLY);
	free(fileinput);
	if (type == 1)
		e->fd_output = open(fileoutput, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	else if (type == 2)
		e->fd_output = open(fileoutput, O_WRONLY | O_APPEND | O_CREAT, 0666);
	free(fileoutput);
	if (e->fd_output < 0 || fdin < 0)
	{
		e->exit_code = 1;
		perror("open");
		return ;
	}
	dup2(e->fd_output, 1);
	dup2(fdin, 0);
	read_and_write(fdin, e->fd_output, e);
}

void	writing(t_env *e, char *fileoutput, int type, char *fileinput)
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
		forking_red(e, fileoutput, type, fileinput);
	else
		waitpid(pid, NULL, 0);
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

void	update_in_out(t_env *e)
{
	int	i;

	i = e->i;
	while (e->v[i] != NULL)
	{
		if (e->v[i][0] == '<')
		{
			e->in_red = i;
			break ;
		}
		else if (e->v[i][0] == '>')
		{
			e->out_red = i;
			break ;
		}
		i++;
	}
}
