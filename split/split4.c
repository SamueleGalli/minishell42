/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 12:27:41 by sgalli            #+#    #+#             */
/*   Updated: 2024/03/25 18:00:09 by sgalli           ###   ########.fr       */
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

int	is_quote(t_env *e, int i)
{
	while (e->cmd[i] != 0 && e->cmd[i] != '\'' \
	&& e->cmd[i] != '\"' && e->cmd[i] != '=')
		i++;
	if ((e->cmd[i] == '=' && e->cmd[i + 1] != 0) \
	&& (e->cmd[i + 1] == '"' || \
	e->cmd[i + 1] == '\''))
		return (1);
	return (0);
}

int	quoting_len(t_env *e)
{
	while (e->cmd[e->j] != 0 && e->cmd[e->j] != '\'' && e->cmd[e->j] != '\"')
	{
		e->j++;
		e->word++;
	}
	return (e->word);
}
