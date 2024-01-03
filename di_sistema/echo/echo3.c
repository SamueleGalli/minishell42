/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 11:50:47 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/03 11:41:37 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	apice_var_quote(t_env *e, int j, int iter, int i)
{
	while (e->env[++iter] != NULL)
	{
		while (e->v[j][e->word] == e->env[iter][i])
		{
			i++;
			e->word++;
		}
		if (e->env[iter][i] == '=' && (e->v[j][e->word] == ' ' \
		|| e->v[j][e->word] == 34 || e->v[j][e->word] == '$' \
		|| e->v[j][e->word] == 0))
		{
			printf_env(e, iter);
			if (e->v[j + 1] != NULL)
				printf(" ");
			return ;
		}
		else
		{
			e->word = e->numb;
			i = 0;
		}
	}
	while (e->v[j][e->word] != 0 && e->v[j][e->word] != ' ' \
	&& e->v[j][e->word] != 34)
		e->word++;
}
