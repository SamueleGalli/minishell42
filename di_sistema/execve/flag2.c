/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:25:01 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/18 10:55:43 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	num_env(t_env *e, char *s, int j, int j2)
{
	int	i;

	e->i_env = j2;
	i = 0;
	j++;
	e->flag_i = j;
	while (s[j] != '\0')
	{
		j++;
		i++;
	}
	return (i);
}

void	flag_while(t_env *e)
{
	while (e->v[e->indx] != NULL && e->numb < e->count
		&& e->v[e->indx][0] != '|')
	{
		if (e->v[e->indx][0] == '$' && e->v[e->indx][1] == '?')
			env_variable(e);
		else if (e->v[e->indx][0] == '$' && e->v[e->indx][1] != '?')
			env_variable2(e);
		else
			split_flag(e);
		e->word++;
		e->indx++;
		e->numb++;
	}
}
