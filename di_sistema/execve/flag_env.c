/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:25:43 by sgalli            #+#    #+#             */
/*   Updated: 2023/11/16 11:53:48 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	alloc_flag_env(t_env *e, int i, int k)
{
	int	i2;
	int	j;

	i2 = 0;
	j = k;
	while (e->env[i][k] != 0 && e->env[i][k] != ' ')
	{
		i2++;
		k++;
	}
	k = j;
	e->mat_flag[e->word] = (char *)malloc(sizeof(char) * (i2 + 1));
	i2 = 0;
	while (e->env[i][k] != 0 && e->env[i][k] != ' ')
	{
		e->mat_flag[e->word][i2] = e->env[i][k];
		i2++;
		k++;
	}
	e->mat_flag[e->word][i2] = '\0';
}

int	enviroment_control(t_env *e, int i, int k)
{
	int	i2;

	i2 = 1;
	if (e->v[e->indx][i2] == e->env[i][k])
	{
		while (e->v[e->indx][i2] == e->env[i][k])
		{
			i2++;
			k++;
		}
		if (e->env[i][k] == '=' && (e->v[e->indx][i2] == '\0'
				|| e->v[e->indx][i2] == ' '))
		{
			k++;
			alloc_flag_env(e, i, k);
		}
	}
	i++;
	return (i);
}

void	env_variable(t_env *e)
{
	int	i;

	i = 0;
	while (e->env[i] != NULL)
		i = enviroment_control(e, i, 0);
}
