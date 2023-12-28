/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:45:48 by eraccane          #+#    #+#             */
/*   Updated: 2023/12/28 12:39:41 by sgalli           ###   ########.fr       */
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
		printf("bash: %s: No such file or directory\n", filename);
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
	int		size;
	char	*s;

	s = e->v[index_v_arrows(e, "<") + 1];
	i = 0;
	size = ft_strlen(s);
	str = (char *)malloc(sizeof(char) * (size + 1));
	while (s[i] != 0 && s[i] != ' ')
	{
		str[i] = s[i];
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
