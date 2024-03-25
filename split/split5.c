/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:15:45 by sgalli            #+#    #+#             */
/*   Updated: 2024/03/25 17:59:34 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	split_normal(t_env *e)
{
	while (e->cmd[e->indx] != ' ' && e->cmd[e->indx] != 0
		&& e->cmd[e->indx] != '|' && e->cmd[e->indx] != '<'
		&& e->cmd[e->indx] != '>')
		e->v[e->i][e->lenght++] = e->cmd[e->indx++];
	if (e->cmd[e->indx] == 34 || e->cmd[e->indx] == 39)
		if (e->cmd[e->indx + 1] == '\0')
			e->v[e->i][e->lenght++] = e->cmd[e->indx++];
	if (e->count == 1)
		e->v[e->i][e->lenght++] = ' ';
}

void	exp_split(t_env *e)
{
	while (e->cmd[e->indx] != ' ' && e->cmd[e->indx] != 0
		&& e->cmd[e->indx] != '|' && e->cmd[e->indx] != '<'
		&& e->cmd[e->indx] != '>' && e->cmd[e->indx] != '"'
		&& e->cmd[e->indx] != '\'')
		e->v[e->i][e->lenght++] = e->cmd[e->indx++];
}
