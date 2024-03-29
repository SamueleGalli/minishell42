/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 21:25:41 by eraccane          #+#    #+#             */
/*   Updated: 2024/03/29 10:33:26 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	double_minor_redirect(t_env *e)
{
	char	*line;
	int		i;

	i = 0;
	alloc_all_here(e);
	line = NULL;
	e->buffer = NULL;
	if (e->cmd != 0)
		add_history(e->cmd);
	here_while(e, line, i);
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
		all = (char *)malloc(sizeof(char) * ft_strlen(buffer) + 1);
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
	e->do_here = 1;
	if (check_builtin(e) == 0)
	{
		pathcmd(e);
		flag_matrix(e);
	}
	else
		e->s = NULL;
	if (redir_file(e) == 1)
	{
		e->i += 2;
		if (e->here_p != 0)
			free(e->here_p);
		close(e->pipefd[1]);
		dup2(e->pipefd[0], STDIN_FILENO);
		close(e->pipefd[0]);
		redirect_mult_double(e);
	}
	else
	{
		close(e->pipefd[1]);
		dup2(e->pipefd[0], STDIN_FILENO);
	}
}

void	continue_heredoc(t_env *e)
{
	if (e->delim != 0)
		free_table(e->delim);
	if (e->v[0][0] != '<')
	{
		init_heredoc(e);
		if (e->s != NULL)
		{
			if (e->c_path == 0 && access(e->s, X_OK) == 0)
				pipe_com(e);
			else
				printf("invalid command %s\n", e->v[e->i]);
			free(e->here_p);
			e->here_p = 0;
		}
		else
			variabletype(e);
	}
	if (e->here_p != 0)
		free(e->here_p);
	exiting(e, 0);
}
