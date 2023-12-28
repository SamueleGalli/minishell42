/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 13:07:09 by eraccane          #+#    #+#             */
/*   Updated: 2023/12/28 12:46:42 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//cat < main.c minishell.h override.supp

#include "../../minishell.h"

void	single_minor_redirect(t_env *e)
{
	int		fd;
	char	*filename;

	e->i += 2;
	if (multi_file(e) >= 2 && e->v[0][0] != '>' && e->v[0][0] != '<')
	{
		while_multiple_file(e, 0);
		return ;
	}
	filename = find_filepath_minor(e);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		e->exit_code = 1;
		printf("bash: %s: No such file or directory\n", filename);
		e->exit = 1;
		free(filename);
		return ;
	}
	free(filename);
	if (e->v[0][0] != '<' && e->v[0][0] != '>')
		single_continuous(e, fd);
	e->exit = 1;
	close(fd);
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
			exiting(e, 0);
		}
		close(fd);
	}
	else
		check_red_fork(e, filename, 1);
}

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
			exiting(e, 0);
		}
		close(fd);
	}
	else
		check_red_fork(e, filename, 2);
}
