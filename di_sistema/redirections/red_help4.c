/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_help4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:23:17 by sgalli            #+#    #+#             */
/*   Updated: 2023/11/10 13:04:38 by sgalli           ###   ########.fr       */
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
		return ;
	}
	close(fd);
}
