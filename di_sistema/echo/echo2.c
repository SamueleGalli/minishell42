/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 10:16:08 by sgalli            #+#    #+#             */
/*   Updated: 2023/10/20 13:07:35 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	mini_get_var(t_env *e, int i, int j)
{
	if (e->v[j][i] == e->env[e->j][e->indx])
	{
		while (e->v[j][i] == e->env[e->j][e->indx])
		{
			i++;
			e->indx++;
		}
		if (e->env[e->j][e->indx] == '=' && (e->v[j][i] == '\0' || \
		e->v[j][i] == ' '))
		{
			e->indx++;
			print_str(e->env[e->j], e->indx);
			if (e->v[j][i] == ' ')
				printf("%c", e->v[j][i]);
			return (-1);
		}
		else
		{
			i = 1;
			e->indx = 0;
		}
	}
	return (i);
}

void	writer(t_env *e, int j)
{
	e->word = 0;
	while (e->v[j][e->word] != 0)
	{
		if (e->v[j][e->word] == '$' && e->v[j][e->word + 1] != '\0')
			get_var_quote(e, j, -1, e->word);
		else
			printf("%c", e->v[j][e->word]);
		e->word++;
	}
}
