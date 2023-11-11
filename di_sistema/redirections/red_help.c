/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:45:48 by eraccane          #+#    #+#             */
/*   Updated: 2023/11/09 17:06:36 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
** NOTE - type == 1 serve per la redirection >
** type == 2 serve per la redirection >>
*/
void	fork_pid_zero(t_env *e, char *filename, int type)
{
	int	fd;

	if (type == 1)
		fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	else if (type == 2)
		fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0666);
	e->i = 0;
	if (fd < 0)
	{
		e->exit_code = 1;
		perror("open");
		exiting(e, 0);
	}
	execve_red(e, fd);
}

void	check_red_fork(t_env *e, char *filename, int type)
{
	pid_t	pid;

	e->s = NULL;
	if (check_builtin(e) == 0)
	{
		pathcmd(e);
		flag_matrix(e);
	}
	if (access(e->s, X_OK) == -1)
		e->exit_code = 1;
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		e->exit = 1;
		exiting(e, 1);
	}
	else if (pid == 0)
		fork_pid_zero(e, filename, type);
	else
		waiting2(e, pid);
	e->exit = 1;
}

int	index_v_arrows(t_env *e, char *s)
{
	int	i;

	i = 0;
	while (e->v[i])
	{
		if (compare(e->v[i], s) == 1)
			return (i);
		i++;
	}
	return (0);
}

int	search_arrows(t_env *e, char *s)
{
	int	i;

	i = 0;
	while (e->v[i] != NULL)
	{
		if (compare(e->v[i], s) == 1)
		{
			if (e->v[i + 1] == NULL && e->v[i] == s)
			{
				perror("Invalid redirection");
				e->exit = 1;
				return (0);
			}
			else
				return (1);
		}
		i++;
	}
	return (0);
}

char	*find_filepath_minor(t_env *e)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)malloc(sizeof(char) * ft_strlen(e->v[index_v_arrows(e, "<")
				+ 1]) + 1);
	while (e->v[index_v_arrows(e, "<") + 1][i] != 0 && \
	e->v[index_v_arrows(e, "<") + 1][i] != ' ')
	{
		str[i] = e->v[index_v_arrows(e, "<") + 1][i];
		i++;
	}
	if (i == 0)
	{
		free(str);
		str = NULL;
	}
	str[i] = '\0';
	return (str);
}
