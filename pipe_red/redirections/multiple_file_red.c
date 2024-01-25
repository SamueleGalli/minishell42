/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_file_red.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 11:45:20 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/25 10:14:59 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	multi_file(t_env *e)
{
	int	out;
	int	i;

	out = 0;
	i = e->i;
	i++;
	while (e->v[i] != 0 && e->v[i][0] != '>'
		&& e->v[i][0] != '|')
	{
		if (e->v[i][0] == '<')
		{
			if (e->v[i + 1] != NULL)
			{
				i ++;
			}
		}
		out++;
		i++;
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

int	check_first(t_env *e, int fd, int i)
{
	char	*file;

	i = i + 1 - 1;
	file = file_loop(e);
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		e->exit_code = 1;
		perror("open");
		if (file != NULL)
			free(file);
		e->exit = 1;
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

	e->i++;
	filename = NULL;
	if (e->v[e->i + 1][0] == '<')
	{
		mult_check_file(e, fd, filename);
		return ;
	}
	if (check_first(e, fd, e->i) == 1)
		return ;
	e->i++;
	cont_while_mult_file(e, fd, filename, 0);
}
