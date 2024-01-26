/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_pipe_and_redirect.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 09:50:43 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/26 11:47:22 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_type(t_env *e)
{
	if (e->v[e->check] == NULL)
		return (0);
	else if (e->v[e->check][0] == '<')
	{
		e->input = e->check;
		return (1);
	}
	else if (e->v[e->check][0] == '|')
	{
		e->piping = 1;
		return (2);
	}
	else if (e->v[e->check][0] == '>')
	{
		e->piping = 1;
		e->output = e->check;
		return (1);
	}
	return (0);
}

int	pipe_or_redir(t_env *e)
{
	e->output = -1;
	e->input = -1;
	e->check = e->i;
	while (e->v[e->check] != NULL && e->v[e->check][0] != '|' \
	&& e->v[e->check][0] != '<' && e->v[e->check][0] != '>')
		e->check++;
	return (check_type(e));
}
