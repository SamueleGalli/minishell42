/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:33:46 by sgalli            #+#    #+#             */
/*   Updated: 2024/03/26 18:03:21 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	waiting(t_env *e)
{
	waitpid(e->pid, &e->status, 0);
	e->exit = 1;
	if (WIFEXITED(e->status) == 0)
		e->exit_code = 2;
	else
		e->exit_code = WEXITSTATUS(e->status);
}

void	com_flag(t_env *e)
{
	singal_fork(e);
	e->pid = fork();
	if (e->pid < 0)
	{
		perror("fork");
		exiting(e, 1);
	}
	else if (e->pid == 0)
	{
		execve(e->s, e->mat_flag, e->env);
		perror("execve");
		exiting(e, 1);
	}
	else
		waiting(e);
}

void	check_valid_file(t_env *e)
{
	DIR	*dir;

	dir = opendir(e->v[e->i]);
	if (dir == NULL)
	{
		if (access(e->s, X_OK) == 0)
		{
			if (access(e->s, R_OK | X_OK) == 0)
				com_flag(e);
		}
		else
		{
			printf("bash: %s: permission denied\n", e->v[e->i]);
			e->exit_code = 126;
		}
	}
	else
	{
		printf("bash: %s: is a directory\n", e->v[e->i]);
		e->exit_code = 126;
		free(dir);
	}
}

void	com(t_env *e)
{
	if (e->v[0][0] == '\'' || e->v[0][0] == '\"')
	{
		print_no_quote(e->v[0], 0);
		printf(" command not found\n");
		e->exit_code = 127;
		return ;
	}
	pathcmd(e);
	flag_matrix(e);
	if (empty(e) == 0)
		return ;
	if (e->c_path == 0 && access(e->s, F_OK) == 0)
		check_valid_file(e);
	else
		error(e);
}
