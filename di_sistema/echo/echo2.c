/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 10:16:08 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/19 12:12:19 by sgalli           ###   ########.fr       */
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
		if (e->env[e->j][e->indx] == '=' && (e->v[j][i] == '\0'
				|| e->v[j][i] == ' '))
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
	while (e->v[j] != NULL && e->v[j][e->word] != 0)
	{
		if (e->v[j][e->word] == '$' && e->v[j][e->word + 1] != 0
			&& e->v[j][e->word + 1] == '?')
		{
			printf("%d", e->exit_code);
			e->word += 2;
		}
		else if (e->v[j][e->word] == '$' && e->v[j][e->word + 1] != '\0')
		{
			if (get_var_quote(e, j, -1, e->word) == 1)
				return ;
			j++;
			e->word = 0;
		}
		else
			short_write(e, j);
	}
}

void	bridge(t_env *e, int j)
{
	if (e->v[j][e->word] == '$' && e->v[j][e->word + 1] == '?')
	{
		printf("%d", e->exit_code);
		e->word = e->word + 2;
		return ;
	}
	e->word++;
	e->numb = e->word;
	apice_var_quote(e, j, -1, 0);
}

void	printf_env(t_env *e, int iter)
{
	int	i;

	i = 0;
	while (e->env[iter][i] != '\0' && e->env[iter][i] != '=')
		i++;
	if (e->env[iter][i] == '=')
	{
		i++;
		while (e->env[iter][i] != 0)
			printf("%c", e->env[iter][i++]);
	}
}
