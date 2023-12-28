/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:26:37 by sgalli            #+#    #+#             */
/*   Updated: 2023/12/28 12:40:49 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// scrivi l'output della pipe nel file1
// ls / | grep c | cat > file1

void	write_red(t_env *e)
{
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

void	forking_in(t_env *e, char *fileoutput, int type)
{
	int	fdout;

	fdout = 0;
	if (type == 1)
		fdout = open(fileoutput, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	else if (type == 2)
		fdout = open(fileoutput, O_WRONLY | O_APPEND | O_CREAT, 0666);
	if (fdout == -1)
	{
		if (fileoutput != NULL)
			free(fileoutput);
		printf("bash: %s: No such file or directory\n", fileoutput);
		exiting(e, 1);
	}
	if (fileoutput != NULL)
		free(fileoutput);
	dup2(fdout, STDOUT_FILENO);
	close(fdout);
	close(e->pipefd[0]);
	close(e->pipefd[1]);
	write_red(e);
}

void	single_write(t_env *e, char *fileoutput, int type)
{
	pid_t	pid;

	e->i = e->check;
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
	{
		waitpid(pid, &e->status, 0);
		if (WIFEXITED(e->status) == 0)
			e->exit_code = 2;
		else
			e->exit_code = WEXITSTATUS(e->status);
		close(e->pipefd[0]);
		close(e->pipefd[1]);
	}
}

void	check_file(t_env *e)
{
	char	*fileoutput;

	e->check = e->i;
	while (e->v[e->i][0] != '>')
		e->i++;
	e->i2 = e->i;
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
	e->i = e->i2;
	e->i = e->i + 2;
}
