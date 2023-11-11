/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:25:01 by sgalli            #+#    #+#             */
/*   Updated: 2023/11/10 19:08:40 by sgalli           ###   ########.fr       */
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

int	venv(t_env *e, int i, int j)
{
	int	k;

	k = 1;
	while (e->env[++i] != NULL)
	{
		if (e->v[e->indx][k] == e->env[i][j] && e->env[i][j] != ' ')
		{
			while (e->v[e->indx][k] == e->env[i][j] \
			&& e->v[e->indx][k] != ' ' && e->v[e->indx][k] != 34)
			{
				k++;
				j++;
			}
			if (e->env[i][j] == '=' && e->v[e->indx][k] == '\0')
				return (num_env(e, e->env[i], j, i));
			else
			{
				k = 1;
				j = 0;
			}
		}
	}
	return (0);
}

void	flag_env(t_env *e)
{
	int	k;
	int	i;
	int	j;

	i = venv(e, -1, 0);
	if (i == 0)
		return ;
	j = 0;
	k = e->flag_i;
	while (e->env[e->i_env][k] != '\0')
	{
		j++;
		k++;
	}
	k = 0;
	e->mat_flag[e->word] = (char *)malloc(sizeof(char) * i + 1);
	while (e->env[e->i_env][e->flag_i] != '\0')
		e->mat_flag[e->word][k++] = e->env[e->i_env][e->flag_i++];
	e->mat_flag[e->word][k] = '\0';
	e->flag_i = 0;
	e->i_env = 0;
}

void	flag_while(t_env *e)
{
	while (e->v[e->indx] != NULL && e->numb < e->count
		&& e->v[e->indx][0] != '|')
	{
		if (e->v[e->indx][0] == '$' && e->v[e->indx][1] == '?')
			flag_env(e);
		else
			split_flag(e);
		e->word++;
		e->indx++;
		e->numb++;
	}
}
