/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:39:03 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/03 11:39:07 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	reading_file(t_env *e)
{
	e->i = e->start_red;
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

void	fork_reading(t_env *e, char *fileinput)
{
	int	fdin;

	fdin = open(fileinput, O_RDONLY);
	free(fileinput);
	if (fdin < 0)
	{
		e->exit_code = 1;
		printf("bash: %s: No such file or directory\n", fileinput);
		return ;
	}
	dup2(fdin, 0);
	close(fdin);
	reading_file(e);
}

void	reading(t_env *e, char *fileinput)
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
		fork_reading(e, fileinput);
	else if (pid > 0)
	{
		waitpid(pid, &e->status, 0);
		if (WIFEXITED(e->status) == 0)
			e->exit_code = 2;
		else
			e->exit_code = WEXITSTATUS(e->status);
	}
}

void	last_file_in(t_env *e)
{
	char	*fileinput;

	e->i = e->in_red;
	fileinput = find_filepath_minor_mult(e);
	reading(e, fileinput);
	if (fileinput != NULL)
		free(fileinput);
	while (e->v[e->i] != NULL && e->v[e->i][0] != '|')
		e->i++;
}
