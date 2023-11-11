/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minor_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 21:25:41 by eraccane          #+#    #+#             */
/*   Updated: 2023/11/08 14:48:41 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	single_continuous(t_env *e, int fd)
{
	pid_t	pid;

	if (check_builtin(e) == 0)
	{
		pathcmd(e);
		flag_matrix(e);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		e->exit = 1;
		exiting(e, 1);
	}
	fork_cotinue(e, pid, fd);
}

char	*update_buffer_red(char *line, char *buffer)
{
	char	*all;
	char	*buf;

	all = NULL;
	all = ft_strcpy(all, buffer);
	buf = ft_strjoin_n(all, line);
	free(buffer);
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

int	check_error_red(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	return (0);
}

// NOTE - can find check_pid_red() in file -> redirections.c
void	redirect_double_arrows(t_env *e, char *buffer)
{
	int		pipe_fd[2];
	pid_t	pid;
	char	*s;

	s = NULL;
	s = ft_strcpy(s, buffer);
	free(buffer);
	if (check_error_red(pipe_fd) == 1)
		return ;
	pid = fork();
	continuing_minor_double(e, s, pipe_fd, pid);
}
