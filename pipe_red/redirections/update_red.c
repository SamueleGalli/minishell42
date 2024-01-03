/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_red.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:32:48 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/03 11:39:10 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_in_out(t_env *e)
{
	int	i;

	i = e->i;
	while (e->v[i] != NULL)
	{
		if (e->v[i][0] == '<')
		{
			e->in_red = i;
			break ;
		}
		else if (e->v[i][0] == '>')
		{
			e->out_red = i;
			break ;
		}
		i++;
	}
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

int	update_redir(t_env *e)
{
	update_in_out(e);
	if (e->v[e->i][0] == '<' && e->v[e->i][0] == '>' \
	&& (e->v[e->i] != NULL))
		e->i++;
	else
	{
		if (check_valid_red(e) == 0)
			return (0);
	}
	if (check_valid_red2(e) == 0)
		return (0);
	return (1);
}
