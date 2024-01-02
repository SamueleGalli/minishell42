/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 10:18:01 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/02 16:29:40 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**cont_new_tmp(t_env *e, char **tmp, int i)
{
	if (e->count_exp != -1)
	{
		e->count_exp = -1;
		tmp[i] = NULL;
		return (tmp);
	}
	tmp[i] = (char *)malloc(sizeof(char) * (len_exp(e->v[e->i], e) + 1));
	alloc_mat_esp(tmp[i], e);
	i++;
	tmp[i] = NULL;
	return (tmp);
}

void	single_export(t_env *e)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (e->env[i] != 0)
	{
		printf("declare -x ");
		while (e->env[i][j] != '=')
			printf("%c", e->env[i][j++]);
		printf("=\"");
		j++;
		while (e->env[i][j])
			printf("%c", e->env[i][j++]);
		printf("\"\n");
		i++;
		j = 0;
	}
	return ;
}

int	next_valid(char *s, t_env *e)
{
	if (compare(e->v[e->i], "export") == 1)
	{
		if (s == 0)
			return (0);
		else
		{
			if (s[0] == '|' || s[0] == '<' || s[0] == '>')
				return (0);
			else
				return (1);
		}
	}
	return (2);
}
