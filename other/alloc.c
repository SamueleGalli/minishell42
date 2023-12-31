/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:36:46 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/05 12:46:50 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**alloc_tmp(t_env *e, char **tmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (e->env[j] != NULL)
	{
		if (j == e->ex)
			change_value(e, i, tmp);
		else
		{
			tmp[i] = (char *)malloc(sizeof(char) * \
			(ft_strlen(e->env[j]) + 1));
			alloc_mat(tmp[i], e->env[j]);
		}
		i++;
		j++;
	}
	tmp[i] = NULL;
	return (tmp);
}

void	alloc_mat(char *d, char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
}

char	*alloc_file(t_env *e, char s)
{
	while (e->v[e->i] != NULL)
	{
		if (e->v[e->i][0] == s)
		{
			e->i++;
			if (e->v[e->i + 1] == NULL || e->v[e->i + 1][0] == '>' \
			|| e->v[e->i + 1][0] == '|')
				return (e->v[e->i]);
		}
		e->i++;
	}
	return (0);
}
