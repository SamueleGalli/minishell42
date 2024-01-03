/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:20:33 by eraccane          #+#    #+#             */
/*   Updated: 2024/01/03 11:37:43 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	index_v_arrows(t_env *e, char *s)
{
	int	i;

	i = 0;
	while (e->v[i])
	{
		if (compare(e->v[i], s) == 1)
			return (i);
		i++;
	}
	return (0);
}

int	search_arrows(t_env *e, char *s)
{
	int	i;

	i = 0;
	while (e->v[i] != NULL)
	{
		if (compare(e->v[i], s) == 1)
		{
			if (e->v[i + 1] == NULL && e->v[i] == s)
			{
				perror("Invalid redirection");
				e->exit = 1;
				return (0);
			}
			else
				return (1);
		}
		i++;
	}
	return (0);
}

int	search_mult_arrows(t_env *e, char *s)
{
	int	i;

	i = e->i;
	while (e->v[i] != NULL)
	{
		if (compare(e->v[i], s) == 1)
			return (1);
		if (e->v[e->i][0] == '>' || e->v[e->i][0] == '<')
			return (0);
		i++;
	}
	return (0);
}
