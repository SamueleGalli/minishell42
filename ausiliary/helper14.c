/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper14.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 11:38:59 by sgalli            #+#    #+#             */
/*   Updated: 2023/12/28 12:39:41 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_red(t_env *e)
{
	int	i;

	i = 0;
	while (e->v[e->i][i] == ' ')
		i++;
	while (e->v[e->i][i] != 0 && e->v[e->i][i] != ' ')
	{
		i++;
	}
	return (i);
}

void	cont_mult_file(t_env *e, int fd, char *filename)
{
	int	i;

	i = e->i;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		if (filename != NULL)
			free(filename);
		e->exit_code = 1;
		printf("bash: %s: No such file or directory\n", filename);
		e->exit = 1;
		return ;
	}
	if (filename != NULL)
		free(filename);
	single_continuous(e, fd);
	e->i = i;
}
