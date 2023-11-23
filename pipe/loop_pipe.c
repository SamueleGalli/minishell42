/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:34:00 by sgalli            #+#    #+#             */
/*   Updated: 2023/11/23 10:57:12 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cont_mult_pipe(t_env *e)
{
	e->pid_pipe = fork();
	if (e->pid_pipe < 0)
	{
		perror("fork");
		exiting(e, 1);
	}
	else if (e->pid_pipe == 0)
		fork_loop(e);
	else
		parent_loop_pipe(e);
}

void	while_cat(t_env *e)
{
	e->cat_pipe = 0;
	while (e->v[e->i] != NULL && e->v[e->i + 1] != NULL)
	{
		if ((compare(e->v[e->i], "cat") == 1 \
		|| compare(e->v[e->i], "cat ") == 1) && e->v[e->i + 1][0] == '|')
		{
			e->cat_pipe = 1;
			update_pipe(e);
		}
		else
			break ;
	}
}

void	init_pipe(t_env *e)
{
	while_cat(e);
	if (e->cat_pipe == 1)
	{
		if (pipe(e->pipefd) == -1)
		{
			perror("pipe");
			exiting(e, 1);
		}
		cont_mult_pipe(e);
	}
	e->i = 0;
}

void	multiple_pipe(t_env *e)
{
	init_pipe(e);
	while (e->p_i < e->c_pipe)
	{
		if (pipe(e->pipefd) == -1)
		{
			perror("pipe");
			exiting(e, 1);
		}
		cont_mult_pipe(e);
		e->p_i++;
		update_pipe(e);
	}
	parent2(e);
}
