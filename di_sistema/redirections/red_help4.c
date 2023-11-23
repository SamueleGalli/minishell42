/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_help4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:23:17 by sgalli            #+#    #+#             */
/*   Updated: 2023/11/23 13:06:22 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	min_mult_redirect(t_env *e)
{
	int		fd;
	char	*filename;

	e->in_red = e->i;
	filename = find_filepath_minor_mult(e);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd < 0)
	{
		e->exit_code = 1;
		e->exit = 1;
		perror("open");
		e->true_red = 1;
		return ;
	}
	close(fd);
}

int	check_valid_red(t_env *e)
{
	while (e->v[e->i] != NULL)
	{
		if (e->v[e->i][0] == '<' || e->v[e->i][0] == '>'
			|| e->v[e->i][0] == '|')
		{
			e->i++;
			break ;
		}
		else if ((e->v[e->i][1] == '>' && e->v[e->i][2] == '>') \
		|| (e->v[e->i][1] == '<' && e->v[e->i][2] == '<') \
		|| e->v[e->i][1] == '<' || e->v[e->i][1] == '>')
		{
			printf("command not found %c\n", e->v[e->i][1]);
			return (0);
		}
		e->i++;
	}
	return (1);
}

int	check_valid_red2(t_env *e)
{
	while (e->v[e->i] != NULL)
	{
		if (e->v[e->i][0] == '<' || e->v[e->i][0] == '>' || \
		e->v[e->i][0] == '|')
			break ;
		else if ((e->v[e->i][1] == '>' && e->v[e->i][2] == '>') \
		|| e->v[e->i][1] == '<' || e->v[e->i][1] == '>')
		{
			printf("command not found %c\n", e->v[e->i][1]);
			return (0);
		}
		e->i++;
	}
	return (1);
}
