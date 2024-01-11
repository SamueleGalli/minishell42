/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   major_red.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 13:07:09 by eraccane          #+#    #+#             */
/*   Updated: 2024/01/11 11:29:58 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	double_major_redirect(t_env *e)
{
	char	*filename;
	int		fd;

	filename = find_filepath(e);
	if (compare(e->v[0], ">>") == 1 || compare(e->v[0], ">> ") == 1)
	{
		fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0666);
		if (fd < 0)
		{
			e->exit_code = 1;
			printf("bash: %s: No such file or directory\n", filename);
			return ;
		}
		close(fd);
	}
	else
		check_red_fork(e, filename, 2);
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

void	single_major_redirect(t_env *e)
{
	char	*filename;
	int		fd;

	filename = find_filepath(e);
	if (compare(e->v[0], ">") == 1 || compare(e->v[0], "> ") == 1)
	{
		fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0666);
		if (fd < 0)
		{
			e->exit_code = 1;
			printf("bash: %s: No such file or directory\n", filename);
			return ;
		}
		close(fd);
	}
	else
		check_red_fork(e, filename, 1);
}

void	single_major_mult_redirect(t_env *e)
{
	char	*filename;
	int		fd;

	filename = find_mult_filepath(e);
	if (e->v[e->i + 1] == NULL)
	{
		printf("error nothing after >\n");
		return ;
	}
	if (compare(e->v[e->i], ">") == 1 || compare(e->v[e->i], "> ") == 1)
	{
		fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0666);
		if (fd < 0)
		{
			e->exit_code = 1;
			e->exit = 1;
			printf("bash: %s: No such file or directory\n", filename);
			return ;
			close(fd);
		}
	}
	else
		check_red_fork(e, filename, 1);
}

void	redirect_mult_double(t_env *e)
{
	char	*filename;
	int		fd;

	filename = find_mult_mult_filepath(e);
	if (compare(e->v[e->i], ">>") == 1 || compare(e->v[e->i], ">> ") == 1)
	{
		fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0666);
		if (fd < 0)
		{
			e->exit_code = 1;
			printf("bash: %s: No such file or directory\n", filename);
			return ;
		}
		close(fd);
	}
	else
		check_red_fork(e, filename, 2);
}
