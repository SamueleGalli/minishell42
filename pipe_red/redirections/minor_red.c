/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minor_red.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 11:38:59 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/25 10:27:20 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	len_red(t_env *e)
{
	int	i;

	i = 0;
	while (e->v[e->i][i] == ' ')
		i++;
	while (e->v[e->i][i] != 0 && e->v[e->i][i] != ' ')
		i++;
	return (i);
}

void	cont_mult_file(t_env *e, int fd, char *filename)
{
	e->i = e->i_tmp;
	if (check_builtin(e) == 0)
	{
		fd = open(filename, O_RDONLY);
		if (fd < 0)
		{
			e->exit_code = 1;
			printf("bash: %s: No such file or directory\n", filename);
			if (filename != NULL)
				free(filename);
			e->exit = 1;
			return ;
		}
	}
	if (filename != NULL)
		free(filename);
	single_continuous(e, fd);
}

int	prev_minor_red(t_env *e, int fd, char *filename)
{
	if (multi_file(e) >= 2 && min_com(e) == 1)
	{
		while_multiple_file(e, 0);
		return (0);
	}
	filename = find_filepath_minor_mult(e);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		if (e->piping == 1)
			print_in_pipe(e);
		perror("open");
		e->exit_code = 1;
		e->exit = 1;
		free(filename);
		return (0);
	}
	free(filename);
	check_next_redp(e);
	single_continuous(e, fd);
	while (e->v[e->i] && e->v[e->i][0] != '|' && e->v[e->i][0] != '>')
		e->i++;
	close(fd);
	return (1);
}

void	min_mult_redirect(t_env *e)
{
	int		fd;
	char	*filename;

	fd = 0;
	filename = NULL;
	if (prev_minor_red(e, fd, filename) == 0)
		return ;
}
