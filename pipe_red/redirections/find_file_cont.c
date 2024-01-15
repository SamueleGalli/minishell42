/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_file_cont.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:35:11 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/15 11:53:29 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*filepath(char *str, int j, t_env *e)
{
	int	d;

	d = 0;
	if (e->v[e->i][0] == '\'' || e->v[e->i][0] == '\"')
	{
		j++;
		while (e->v[e->i][0] != 0 && \
		e->v[e->i][j] != e->v[e->i][0])
			str[d++] = e->v[e->i][j++];
	}
	else
	{
		while (e->v[e->i][j] != 0 && e->v[e->i][j] != ' ')
		{
			if (e->v[e->i][j] == '\'' || e->v[e->i][j] == '\"')
				j++;
			else
				str[d++] = e->v[e->i][j++];
		}
	}
	str[d] = '\0';
	return (str);
}

void	error_fd(t_env *e)
{
	e->exit_code = 1;
	perror("open");
	if (e->filename != NULL)
		free(e->filename);
	exiting(e, 1);
}

int	loop_file(t_env *e, int fd, int type)
{
	fd = 0;
	while (e->v[e->i] != NULL)
	{
		if (type == 1)
			fd = open(e->filename, O_WRONLY | O_TRUNC | O_CREAT, 0666);
		else if (type == 2)
			fd = open(e->filename, O_WRONLY | O_APPEND | O_CREAT, 0666);
		if (fd < 0)
			error_fd(e);
		if (e->v[e->i + 1] != NULL && e->v[e->i + 1][0] == '>')
		{
			e->i = e->i + 1;
			if (e->v[e->i][1] == '>')
				type = 2;
			else
				type = 1;
			if (e->filename != NULL)
				free(e->filename);
			e->filename = find_filepath_major(e);
		}
		else
			return (fd);
	}
	return (fd);
}
