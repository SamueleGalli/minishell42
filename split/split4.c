/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 12:27:41 by sgalli            #+#    #+#             */
/*   Updated: 2024/03/23 12:18:46 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_next_car(t_env *e)
{
	e->indx += 2;
	if (e->cmd[e->indx] != ' ')
	{
		e->word++;
		return ;
	}
	e->q_null = 1;
	e->word++;
}

int	if_only_space(t_env *e)
{
	int	i;

	i = 0;
	while (e->cmd[i] == ' ' && e->cmd[i] != 0)
		i++;
	if (e->cmd[i] == 0)
		return (1);
	else
		return (0);
}

int	check_quote_sindoub(t_env *e)
{
	if ((e->cmd[e->j + 1] == '\'' && e->cmd[e->j] == e->cmd[e->j + 1]) || \
	(e->cmd[e->j + 1] == '\"' && e->cmd[e->j] == e->cmd[e->j + 1]))
		return (1);
	else
		return (0);
}
