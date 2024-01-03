/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_file_red.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 11:45:20 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/03 11:38:22 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	multi_file(t_env *e)
{
	int	out;

	out = 0;
	while (e->v[e->i] != 0 && e->v[e->i][0] != '<' && e->v[e->i][0] != '>'
		&& e->v[e->i][0] != '|')
	{
		out++;
		e->i++;
	}
	return (out);
}

char	*file_loop(t_env *e)
{
	char	*s;
	int		i;
	int		j;

	j = 0;
	i = len_red(e);
	if (e->v[e->i][0] == '\'' || e->v[e->i][0] == '\"')
		i = i - 2;
	s = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (e->v[e->i][i] == ' ')
		i++;
	if (e->v[e->i][i] == '\'' || e->v[e->i][i] == '\"')
		i++;
	while (e->v[e->i][i] && e->v[e->i][i] != ' ' && \
	e->v[e->i][i] != '\'' && e->v[e->i][i] != '\"')
		s[j++] = e->v[e->i][i++];
	s[j] = 0;
	return (s);
}

void	loop_error_min(t_env *e, int fd, char *file, int i)
{
	e->i = i;
	while (e->v[e->i] != 0 && e->v[e->i][0] != '<' && e->v[e->i][0] != '>' \
	&& e->v[e->i][0] != '|')
	{
		file = file_loop(e);
		fd = open(file, O_RDONLY);
		if (fd < 0)
		{
			printf("%s", file);
			if (file != NULL)
				free(file);
		}
		fd = 0;
		e->i++;
	}
	printf(": No such file or directory\n");
}

int	check_first(t_env *e, int fd, int i)
{
	char	*file;

	file = file_loop(e);
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		e->exit_code = 1;
		printf("bash: %s", file);
		if (file != NULL)
			free(file);
		e->exit = 1;
		loop_error_min(e, fd, file, ++i);
		return (1);
	}
	else
	{
		if (file != NULL)
			free(file);
		return (0);
	}
}

void	while_multiple_file(t_env *e, int fd)
{
	char	*filename;

	e->i = 3;
	if (check_first(e, fd, --e->i) == 1)
		return ;
	e->i++;
	while (e->v[e->i] != NULL)
	{
		filename = file_loop(e);
		cont_mult_file(e, fd, filename);
		e->i++;
	}
}
