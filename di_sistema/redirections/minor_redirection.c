/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minor_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 21:25:41 by eraccane          #+#    #+#             */
/*   Updated: 2023/12/28 12:17:21 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	single_continuous(t_env *e, int fd)
{
	pid_t	pid;

	e->i = 0;
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

char	*alloc_s(char *buf)
{
	int		i;
	char	*t;

	t = (char *)malloc(sizeof(char ) * ft_strlen(buf) + 1);
	i = 0;
	while (buf[i] != 0)
	{
		t[i] = buf[i];
		i++;
	}
	t[i] = 0;
	return (t);
}

void	redirect_double_arrows(t_env *e, char *buffer)
{
	pid_t	pid;
	char	*s;

	s = alloc_s(buffer);
	free(buffer);
	pid = fork();
	continuing_minor_double(e, s, pid);
}
