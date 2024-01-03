/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_file_cont.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:35:11 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/03 11:37:21 by sgalli           ###   ########.fr       */
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

char	*filepath(char *str, int i, int j, t_env *e)
{
	int	d;

	while (e->v[i] != NULL)
	{
		if (e->v[e->i][0] == '<')
		{
			i++;
			break ;
		}
		i++;
	}
	d = 0;
	if (e->v[i][0] == '\'' || e->v[i][0] == '\"')
		j++;
	while (e->v[i][j] != 0 && \
	e->v[i][j + 1] != ' ' && e->v[i][j] != '\'' && \
	e->v[i][j] != '\"')
		str[d++] = e->v[i][j++];
	str[d] = '\0';
	return (str);
}
