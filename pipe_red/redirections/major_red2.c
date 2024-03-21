/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   major_red2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 11:17:01 by sgalli            #+#    #+#             */
/*   Updated: 2024/03/21 14:26:02 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	single_red(t_env *e)
{
	int	i;

	i = e->i;
	while (e->v[i] != NULL && e->v[i][0] != '|' && e->v[i][0] != '>')
		i++;
	if (e->v[i] == NULL || e->v[i][0] == '|')
		return (1);
	else
		return (0);
}

int	single_file(t_env *e, int fd, int type)
{
	int	i;

	i = e->i - 1;
	if (e->v[i][1] == '>')
		type = 2;
	else
		type = 1;
	fd = opening_file(e, fd, type);
	return (fd);
}

void	fd_in(t_env *e, int j, int i)
{
	int	fd;

	if (e->v[e->i] == NULL || e->v[e->i][0] == '|')
	{
		e->i = i;
		close(0);
		return ;
	}
	e->i = j;
	e->filename = find_filepath_minor_mult(e);
	fd = open(e->filename, O_RDONLY);
	if (fd < 0)
	{
		if (e->no_print == 0)
			perror("open");
		e->exit = 1;
		free(e->filename);
		exiting(e, 1);
	}
	e->i = i;
	dup2(fd, 0);
	free(e->filename);
	close(fd);
}

void	in_major(t_env *e)
{
	int	i;
	int	j;

	i = e->i;
	while (e->v[e->i][0] != '>')
		e->i++;
	while (e->v[e->i] != NULL && e->v[e->i][0] != '|')
	{
		if (e->v[e->i][0] == '<')
		{
			if (access(e->v[e->i + 1], F_OK) == -1)
			{
				perror("open");
				e->exit = 1;
				exiting(e, 1);
			}
			else
				j = e->i;
		}
		e->i++;
	}
	fd_in(e, j, i);
}
