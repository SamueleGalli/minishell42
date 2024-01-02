/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_file_red.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 11:45:20 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/02 16:27:16 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	multi_file(t_env *e)
{
	int	out;

	out = 0;
	while (e->v[e->i] != 0 && e->v[e->i][0] != '<' && e->v[e->i][0] != '>'
		&& e->v[e->i][0] != '|')
	{
		out++;
		e->i++;
	}
	return (out);
}

char	*file_loop(t_env *e)
{
	char	*s;
	int		i;
	int		j;

	j = 0;
	i = len_red(e);
	s = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (e->v[e->i][i] == ' ')
		i++;
	while (e->v[e->i][i] && e->v[e->i][i] != ' ')
		s[j++] = e->v[e->i][i++];
	s[j] = 0;
	return (s);
}

void	while_multiple_file(t_env *e, int fd)
{
	char	*filename;

	e->i = 3;
	while (e->v[e->i] != NULL)
	{
		filename = file_loop(e);
		cont_mult_file(e, fd, filename);
		e->i++;
	}
}
