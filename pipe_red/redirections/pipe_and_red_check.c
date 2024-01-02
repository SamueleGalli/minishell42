/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and_red_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 11:28:01 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/02 16:23:40 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_red_other(t_env *e)
{
	if (e->cmd[e->indx] == '|' || e->cmd[e->indx] == '<'
		|| e->cmd[e->indx] == '>')
	{
		while ((e->cmd[e->indx] == '|' || e->cmd[e->indx] == '<'
				|| e->cmd[e->indx] == '>'))
			e->indx++;
		e->word++;
	}
}

void	splong_red(t_env *e)
{
	while (e->cmd[e->j] == '|' || e->cmd[e->j] == '<' || e->cmd[e->j] == '>')
	{
		e->j++;
		e->word++;
	}
}

void	write_redir(t_env *e)
{
	while (e->cmd[e->indx] == '|' || e->cmd[e->indx] == '<'
		|| e->cmd[e->indx] == '>')
		e->v[e->i][e->lenght++] = e->cmd[e->indx++];
}

int	is_pipredir(char *s)
{
	if (s[0] == '|' || s[0] == '<' || s[0] == '>')
		return (1);
	return (0);
}
