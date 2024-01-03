/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:26:37 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/03 11:40:16 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cont_do_pipe(t_env *e)
{
	if (e->c_pipe == 0)
	{
		if (pipe(e->pipefd) == -1)
		{
			perror("pipe");
			exiting(e, 1);
		}
		parent_pipe_red(e);
		update_pipe(e);
	}
	e->check_input = -1;
}

void	input_pipe(t_env *e)
{
	if (e->check_input == 1)
	{
		e->check = e->i;
		e->i = 0;
		if (pipe(e->pipefd) == -1)
		{
			perror("pipe");
			exiting(e, 1);
		}
		red_pipe_fork(e);
		e->i = e->check;
		e->tmp_i = 1;
	}
}

void	control_pipe(t_env *e)
{
	e->tmp_i = 0;
	e->check = e->i;
	e->c_pipe = 0;
	e->p_i = 0;
	count_pipe(e);
	if (e->v[e->i][0] == '|')
		e->i++;
	if (e->check_input > 0)
		input_pipe(e);
	while (e->v[e->check] != NULL && e->v[e->check][0] != '>' && \
	e->v[e->check][0] != '<')
		e->check++;
	if (e->v[e->check] != NULL)
	{
		if (e->v[e->check][0] == '>' && e->v[e->check + 1] != NULL && \
		e->v[e->check + 2] != NULL)
		{
			e->check++;
			e->start_red = e->check;
		}
		else
			e->c_pipe++;
	}
}

int	check_out_red(t_env *e)
{
	int	i;

	i = e->i;
	while (e->v[i] != NULL && e->v[i][0] != '>')
	{
		if (e->v[i][0] == '|')
			return (0);
		i++;
	}
	if (e->v[i] == NULL)
		return (0);
	else
		return (1);
}

void	do_pipe(t_env *e)
{
	control_pipe(e);
	while (e->p_i < e->c_pipe && e->v[e->i] != NULL && \
	e->v[e->i][0] != '>' && e->v[e->i][0] != '<')
	{
		if (check_out_red(e) == 1)
		{
			check_file(e);
			return ;
		}
		if (pipe(e->pipefd) == -1)
		{
			perror("pipe");
			exiting(e, 1);
		}
		define_redir(e);
		if (e->define_pipe == 3)
			return ;
		if (e->define_pipe != 5 && e->define_pipe != 2)
			update_pipe(e);
		e->p_i++;
	}
	cont_do_pipe(e);
}
