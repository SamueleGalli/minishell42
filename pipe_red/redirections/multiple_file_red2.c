/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_file_red2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:46:51 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/24 11:34:23 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_mult_file(t_env *e)
{
	e->i++;
	if (e->v[e->i] != NULL && \
	e->v[e->i][0] == '<' && e->v[e->i][1] == '<')
	{
		e->i = e->i + 2;
		e->i_here = e->i - 2;
	}
	else if (e->v[e->i] != NULL && e->v[e->i][0] == '<' \
	&& e->v[e->i + 1] != NULL)
		e->i++;
}

void	mult_check_file(t_env *e, int fd, char *filename)
{
	while (e->v[e->i] != NULL && e->v[e->i][0] != '>' && e->v[e->i][0] != '|')
	{
		filename = file_loop(e);
		fd = open(filename, O_RDONLY);
		if (fd < 0)
		{
			if (e->i_here > 0)
				e->i = e->i_here;
			e->exit_code = 1;
			perror("open");
			free(filename);
			return ;
		}
		free(filename);
		update_mult_file(e);
	}
	if (e->v[e->i] == NULL)
		single_continuous(e, fd);
	e->i = e->i_here;
	return ;
}

void	cont_while_mult_file(t_env *e, int fd, char *filename, int i)
{
	if (compare(e->v[e->i_tmp], "echo ") == 1 || \
		compare(e->v[e->i_tmp], "echo") == 1)
	{
		filename = file_loop(e);
		cont_mult_file(e, fd, filename);
		return ;
	}
	while (e->v[e->i] != NULL)
	{
		i = e->i;
		filename = file_loop(e);
		cont_mult_file(e, fd, filename);
		e->i = i;
		e->i++;
	}
}
