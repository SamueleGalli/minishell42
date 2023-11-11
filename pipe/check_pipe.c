/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:30:26 by sgalli            #+#    #+#             */
/*   Updated: 2023/11/10 17:04:28 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	search_pipe(t_env *e)
{
	int	i;

	i = e->i;
	while (e->v[i] != NULL)
	{
		if (e->v[i][0] == '|')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	valid_pipe(t_env *e)
{
	if (e->v[0][0] == '|')
	{
		printf("error parse error near `|'\n");
		e->exit = 1;
		e->exit_code = 1;
		return (1);
	}
	return (0);
}

void	count_pipe(t_env *e)
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
}

void	update_pipe(t_env *e)
{
	if (e->v[e->i] != NULL)
	{
		while (e->v[e->i] != NULL && e->v[e->i][0] != '|' \
		&& e->v[e->i][0] != '<' && e->v[e->i][0] != '>')
			e->i++;
		if (e->v[e->i] == NULL)
			return ;
		if (e->v[e->i][0] == '<' || e->v[e->i][0] == '>')
			return ;
		if (e->v[e->i] != NULL)
			e->i++;
	}
}
