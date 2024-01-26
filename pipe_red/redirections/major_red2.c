/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   major_red2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 11:17:01 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/26 13:38:35 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	single_red(t_env *e)
{
	int	i;

	i = e->i;
	while (e->v[i] != NULL && e->v[i][0] != '|' && e->v[i][0] != '>')
		i++;
	if (e->v[i] == NULL || e->v[i][0] == '|')
		return (1);
	else
		return (0);
}

int	single_file(t_env *e, int fd, int type)
{
	if (e->v[e->i][1] == '>')
		type = 2;
	else
		type = 1;
	fd = opening_file(e, fd, type);
	return (fd);
}
