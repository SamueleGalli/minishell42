/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:45:51 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/02 16:55:07 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*find_filepath(t_env *e)
{
	int	i;

	i = 0;
	while (e->v[i + 1] != NULL)
		i++;
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

char	*find_filepath_minor(t_env *e)
{
	int		i;
	char	*str;
	int		size;
	char	*s;

	s = e->v[index_v_arrows(e, "<") + 1];
	i = 0;
	size = ft_strlen(s);
	if (s[0] == '\'' || s[0] == '\"')
		size -= 2;
	str = (char *)malloc(sizeof(char) * (size + 1));
	return (final_while(str, i, s));
}
