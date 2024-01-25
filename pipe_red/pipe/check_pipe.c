/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:30:26 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/24 15:46:16 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_pipe(t_env *e)
{
	int	i;

	i = e->i;
	while (e->v[i] != NULL && e->v[i][0] != '|')
		i++;
	if (e->v[i] != NULL && e->v[i][0] == '|')
		i++;
	e->i_tmp = i;
	e->i = i;
}

int	exits_pipe(t_env *e)
{
	int	i;

	i = e->i;
	e->c_pipe = 0;
	while (e->v[i] != NULL)
	{
		if (e->v[i][0] == '|')
			e->c_pipe++;
		i++;
	}
	if (e->c_pipe > 0)
		return (1);
	return (0);
}

void	control_pipe(t_env *e)
{
	e->tmp_i = 0;
	e->check = e->i;
	if (e->v[e->i][0] == '|')
		e->i++;
}

int	which_pipe(t_env *e)
{
	int	i;

	i = e->i;
	while (e->v[i] != NULL && e->v[i][0] != '|')
		i++;
	if (e->v[i] == NULL)
		return (1);
	return (0);
}
