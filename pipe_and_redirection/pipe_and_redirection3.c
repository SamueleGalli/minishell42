/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and_redirection3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:38:05 by sgalli            #+#    #+#             */
/*   Updated: 2023/11/10 18:33:53 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_pipefd(t_env *e)
{
	if (e->p_i == 0)
	{
		dup2(e->pipefd[0], STDIN_FILENO);
		close(e->pipefd[0]);
		dup2(e->pipefd[1], STDOUT_FILENO);
		close(e->pipefd[1]);
	}
	else
	{
		close(e->pipefd[0]);
		dup2(e->pipefd[1], STDOUT_FILENO);
		close(e->pipefd[1]);
	}
}

void	fork_loop_redir(t_env *e)
{
	check_pipefd(e);
	if (check_builtin(e) == 0)
	{
		pathcmd(e);
		flag_matrix(e);
	}
	else
		e->s = NULL;
	if (e->s != NULL)
	{
		if (e->c_path == 0 && access(e->s, X_OK) == 0)
			pipe_com(e);
		exiting(e, 0);
	}
	else
		variabletype(e);
	exiting(e, 0);
}

void	find_first_command(t_env *e)
{
	int	i;

	i = 0;
	while (e->v[i] != NULL)
	{
		if (e->v[i][0] == '|')
			break ;
		i++;
	}
	if (e->v[i] == NULL)
		return ;
	while (e->v[i] != NULL && e->v[i][0] != '>' && e->v[i][0] != '<')
		i++;
	if (e->v[i] == NULL)
		return ;
	while (e->v[i] != NULL)
	{
		if (e->v[i][0] == '|')
			break ;
		i--;
	}
	i++;
	e->init_red = i;
}