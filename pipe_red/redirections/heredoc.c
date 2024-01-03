/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 21:25:41 by eraccane          #+#    #+#             */
/*   Updated: 2024/01/03 11:37:54 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	double_minor_redirect(t_env *e)
{
	char	*delim;
	char	*line;
	char	*buffer;

	delim = e->v[index_v_arrows(e, "<<") + 1];
	line = NULL;
	buffer = NULL;
	while (1)
	{
		line = readline("> ");
		singals(e);
		if (check_signals_red(e, line) == 1)
			break ;
		if (compare(line, delim) == 1)
		{
			redirect_double_arrows(e, buffer);
			break ;
		}
		else
			buffer = update_buffer_red(line, buffer);
	}
	e->red_flag = 1;
	e->exit = 1;
}

char	*update_buffer_red(char *line, char *buffer)
{
	char	*all;
	char	*buf;

	all = NULL;
	if (buffer != NULL)
		all = (char *)malloc(sizeof(char ) * ft_strlen(buffer) + 1);
	all = ft_strcpy(all, buffer);
	buf = ft_strjoin_n(all, line);
	free(buffer);
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
	if (check_builtin(e) == 0 && compare(e->v[0], "cat") == 0)
	{
		e->i = 0;
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
			if (compare(e->v[0], "cat") == 1)
				printf("%s", s);
			else
				variabletype(e);
		}
	}
	free(s);
	exiting(e, 1);
}
