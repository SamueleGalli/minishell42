/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_file_cont.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:35:11 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/08 10:14:26 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*find_mult_filepath(t_env *e)
{
	int		i;

	i = e->i;
	while (e->v[i] != NULL)
	{
		if (compare(e->v[i], ">") == 1)
		{
			i++;
			break ;
		}
		i++;
	}
	return (e->v[i]);
}

char	*filepath(char *str, int j, t_env *e)
{
	int	d;

	d = 0;
	if (e->v[e->i][0] == '\'' || e->v[e->i][0] == '\"')
	{
		j++;
		while (e->v[e->i][0] != 0 && \
		e->v[e->i][j] != e->v[e->i][0])
			str[d++] = e->v[e->i][j++];
	}
	else
	{
		while (e->v[e->i][j] != 0 && \
		e->v[e->i][j + 1] != ' ')
			str[d++] = e->v[e->i][j++];
	}
	str[d] = '\0';
	return (str);
}
