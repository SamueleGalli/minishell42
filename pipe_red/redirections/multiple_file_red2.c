/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_file_red2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:46:51 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/16 12:57:42 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	mult_check_file(t_env *e, int fd, char *filename)
{
	while (e->v[e->i] != NULL && e->v[e->i][0] != '>' && e->v[e->i][0] != '|')
	{
		filename = file_loop(e);
		fd = open(filename, O_RDONLY);
		if (fd < 0)
		{
			e->exit_code = 1;
			perror("open");
			free(filename);
			return ;
		}
		free(filename);
		e->i++;
		if (e->v[e->i] != NULL && e->v[e->i][0] == '<' \
		&& e->v[e->i + 1] != NULL)
			e->i++;
	}
	if (e->v[e->i] == NULL)
		single_continuous(e, fd);
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
