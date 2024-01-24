/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 21:25:41 by eraccane          #+#    #+#             */
/*   Updated: 2024/01/24 10:46:21 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	double_minor_redirect(t_env *e)
{
	char	*line;
	char	*buffer;
	int		i;

	i = 0;
	alloc_all_here(e);
	line = NULL;
	buffer = NULL;
	here_while(e, line, buffer, i);
	e->red_flag = 1;
	e->exit = 1;
}

char	*update_buffer_red(char *line, char *buffer, t_env *e)
{
	char	*all;
	char	*buf;

	all = NULL;
	if (line[0] == '$')
		line = convert_line(line, e, 0, 0);
	if (buffer != NULL)
		all = (char *)malloc(sizeof(char ) * ft_strlen(buffer) + 1);
	all = ft_strcpy(all, buffer);
	buf = ft_strjoin_n(all, line);
	free(buffer);
	free(line);
	free(all);
	return (buf);
}

int	check_signals_red(t_env *e, char *line)
{
	if (e->exit_code == 130)
		return (1);
	if (line == NULL)
	{
		errno = EINTR;
		perror("minishell: warning");
		return (1);
	}
	return (0);
}

void	init_heredoc(t_env *e)
{
	e->i = e->i_tmp;
	if (check_builtin(e) == 0 && compare(e->v[e->i], "cat") == 0)
	{
		pathcmd(e);
		flag_matrix(e);
	}
	else
		e->s = NULL;
}

void	continue_heredoc(t_env *e, char *s)
{
	if (e->v[0][0] != '<')
	{
		init_heredoc(e);
		if (e->s != NULL)
		{
			if (e->c_path == 0 && access(e->s, X_OK) == 0)
				pipe_com(e);
			free(s);
		}
		else
		{
			if (e->here_pipe == 1)
				pipe_here(e);
			if (compare(e->v[e->i], "cat") == 1)
				printf("%s", s);
			else
				variabletype(e);
		}
	}
	free(s);
	free_table(e->delim);
	exiting(e, 0);
}
