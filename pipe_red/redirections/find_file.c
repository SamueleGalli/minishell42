/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:45:51 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/29 11:02:03 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	opening_file(t_env *e, int fd, int type)
{
	if (type == 1)
		fd = open(e->filename, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	else if (type == 2)
		fd = open(e->filename, O_WRONLY | O_APPEND | O_CREAT, 0666);
	if (fd < 0)
	{
		e->exit_code = 1;
		if (e->no_here == 0 && e->no_print == 0)
			perror("open");
		if (e->filename != NULL)
			free(e->filename);
		exiting(e, 1);
	}
	return (fd);
}

int	loop_file(t_env *e, int fd, int type)
{
	while (e->v[e->i] != NULL)
	{
		fd = opening_file(e, fd, type);
		if (e->v[e->i + 1] != NULL && check_last_major(e) == 1)
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

char	*find_filepath_major(t_env *e)
{
	char	*str;
	int		j;
	int		d;

	j = 0;
	d = ft_strlen_red(alloc_file(e, '>')) + 1;
	if (d == 1)
		return (NULL);
	str = (char *)malloc(sizeof(char) * d);
	return (filepath(str, j, e));
}

char	*find_filepath_minor_mult(t_env *e)
{
	char	*str;
	int		j;
	int		d;

	j = 0;
	d = ft_strlen_red(alloc_file(e, '<')) + 1;
	str = (char *)malloc(sizeof(char) * d);
	return (filepath(str, j, e));
}
