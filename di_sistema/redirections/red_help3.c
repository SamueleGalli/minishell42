/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_help3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:35:11 by sgalli            #+#    #+#             */
/*   Updated: 2023/11/10 11:45:47 by sgalli           ###   ########.fr       */
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

char	*find_mult_mult_filepath(t_env *e)
{
	int		i;

	i = e->i;
	while (e->v[i] != NULL)
	{
		if (compare(e->v[i], ">>") == 1)
		{
			i++;
			break ;
		}
		i++;
	}
	return (e->v[i]);
}

char	*alloc_file(t_env *e, char s)
{
	int	i;

	i = e->i;
	while (e->v[i] != NULL)
	{
		if (e->v[e->i][0] == s)
		{
			i++;
			return (e->v[i]);
		}
		i++;
	}
	return (0);
}

char	*find_filepath_minor_mult(t_env *e)
{
	int		i;
	char	*str;
	int		j;
	int		d;

	i = e->i;
	j = 0;
	d = ft_strlen_red(alloc_file(e, '<')) + 1;
	str = (char *)malloc(sizeof(char) * d);
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
	while (e->v[i][j] != 0 && \
	e->v[i][j + 1] != ' ')
		str[d++] = e->v[i][j++];
	str[d] = '\0';
	return (str);
}

int	search_mult_arrows(t_env *e, char *s)
{
	int	i;

	i = e->i;
	while (e->v[i] != NULL)
	{
		if (compare(e->v[i], s) == 1)
			return (1);
		if (e->v[e->i][0] == '>' || e->v[e->i][0] == '<')
			return (0);
		i++;
	}
	return (0);
}
