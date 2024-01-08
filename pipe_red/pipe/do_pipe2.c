/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipe2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:06:17 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/08 13:06:37 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	other_redir(t_env *e)
{
	e->check = e->i;
	e->define_pipe = 0;
	while (e->v[e->check] != NULL)
	{
		if (e->v[e->check][0] == '<' || \
		e->v[e->check][0] == '>' || e->v[e->check][0] == '|')
		{
			if (e->in_red > 0 && e->input != -1)
				e->define_pipe = 5;
			else if (e->v[e->check][0] == '|')
				e->define_pipe = 1;
			else if (e->v[e->check][0] == '>')
				e->define_pipe = 2;
			else if (e->v[e->check][0] == '<')
				e->define_pipe = 3;
			break ;
		}
		e->check++;
	}
	e->check = 0;
}

void	zero_input(t_env *e)
{
	e->check = e->i;
	e->i = 0;
	e->pid_pipe = fork();
	if (e->pid_pipe < 0)
	{
		perror("fork");
		exiting(e, 1);
	}
	else if (e->pid_pipe == 0)
		pipe_loop_redir(e);
	else
		parent_process(e);
	e->i = e->check;
}

void	red_pipe_fork(t_env *e)
{
	e->pid_pipe = fork();
	if (e->pid_pipe < 0)
	{
		perror("fork");
		exiting(e, 1);
	}
	else if (e->pid_pipe == 0)
		pipe_loop_redir(e);
	else
		parent_process(e);
}

int	find_red_pipe(t_env *e)
{
	int	i;

	i = e->i;
	while (e->v[i] != NULL)
	{
		if (e->v[i][0] == '>' || e->v[i][0] == '<')
		{
			return (1);
			e->i_tmp = e->i;
			e->i = i;
		}
		i++;
	}
	return (0);
}

void	define_redir(t_env *e)
{
	if (find_red_pipe(e) == 1)
		red_type(e);
	other_redir(e);
	if (e->define_pipe == 0)
	{
		parent_pipe_red(e);
		return ;
	}
	red_pipe_fork(e);
}
