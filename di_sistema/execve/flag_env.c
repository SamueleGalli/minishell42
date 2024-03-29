/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:25:43 by sgalli            #+#    #+#             */
/*   Updated: 2024/03/29 11:11:21 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	env_variable(t_env *e)
{
	char	*s;

	s = ft_itoa(e->exit_code);
	e->mat_flag[e->word] = malloc(ft_strlen(s) + 1);
	strcpy(e->mat_flag[e->word], s);
	free(s);
}

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

void	env_variable2(t_env *e)
{
	int	i;

	i = 0;
	if (e->v[e->indx][1] == ' ' || e->v[e->indx][1] == 0)
	{
		e->indx++;
		return ;
	}
	while (e->env[i] != NULL)
		i = enviroment_control(e, i, 0);
	if (e->env[i] == NULL)
		e->mat_flag[e->word] = NULL;
}
