/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:33:46 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/15 12:05:10 by sgalli           ###   ########.fr       */
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

void	com(t_env *e)
{
	pathcmd(e);
	flag_matrix(e);
	if (empty(e) == 0)
		return ;
	else if (e->c_path == 0 && access(e->s, X_OK) == 0)
		com_flag(e);
	else
		error(e);
}
