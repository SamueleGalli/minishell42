/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:20:33 by eraccane          #+#    #+#             */
/*   Updated: 2024/01/29 11:01:23 by sgalli           ###   ########.fr       */
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

void	check_next_redp(t_env *e)
{
	int	i;

	i = e->i;
	while (e->v[i] != NULL)
	{
		if (e->v[i][0] == '>')
		{
			e->piping = 0;
			return ;
		}
		if (e->v[i][0] == '|')
		{
			e->piping = 1;
			return ;
		}
		i++;
	}
}

void	error_perror(t_env *e, int fd)
{
	if (fd < 0)
	{
		if (e->no_print == 0)
			perror("open");
		e->exit = 1;
		free(e->filename);
		exiting(e, 1);
	}
}
