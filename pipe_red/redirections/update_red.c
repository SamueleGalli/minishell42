/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_red.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:32:48 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/23 12:29:28 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_valid_red(t_env *e)
{
	while (e->v[e->i] != NULL && e->v[e->i][0] != '|')
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

int	update_redir(t_env *e)
{
	if (e->v[e->i] == NULL)
		return (1);
	if (check_valid_red(e) == 0)
		return (0);
	if (check_valid_red2(e) == 0)
		return (0);
	return (1);
}
