/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:31:58 by sgalli            #+#    #+#             */
/*   Updated: 2023/11/21 12:36:26 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cont_first_input(t_env *e, int i)
{
	while (e->v[i] != NULL && e->v[i][0] != '>' && e->v[i][0] != '<')
	{
		if (e->v[i][0] == '|')
		{
			i++;
			while (e->v[i] != NULL && e->v[i][0] != '>' && e->v[i][0] != '<')
			{
				if (e->v[i][0] == '|')
				{
					e->check_input = 1;
					break ;
				}
				i++;
			}
			break ;
		}
		i++;
	}
}

void	check_first_input(t_env *e)
{
	int	i;

	i = 0;
	while (e->v[i] != NULL)
	{
		if (e->v[i][0] == '<')
			break ;
		i++;
	}
	if (e->v[i] == NULL)
		return ;
	if (e->v[i][0] == '<')
		cont_first_input(e, ++i);
}
