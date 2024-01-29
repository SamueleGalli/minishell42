/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_red_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:11:31 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/29 10:48:19 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	redirect_mult_single(t_env *e)
{
	if (e->v[e->i][0] == '>')
		redirect_mult_double(e);
	else if (search_mult_arrows(e, "< ") == 1 \
	|| search_mult_arrows(e, "<") == 1)
		min_mult_redirect(e);
	if (e->v[e->i] != NULL && e->v[e->i + 1] != NULL \
	&& (compare(e->v[e->i], "<< ") == 1 || \
	compare(e->v[e->i], "<<") == 1))
		double_minor_redirect(e);
	if (e->delim != NULL)
		free_table(e->delim);
}

char	*find_lasth_filepath(t_env *e)
{
	int		i;
	char	*str;
	int		j;
	int		d;

	i = e->i;
	j = 0;
	d = ft_strlen_red(alloc_file(e, '>')) + 1;
	str = (char *)malloc(sizeof(char) * d);
	while (e->v[i] != NULL)
	{
		if (e->v[i][0] == '>')
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

int	check_last_major(t_env *e)
{
	while (e->v[e->i] != NULL && e->v[e->i][0] != '|' && \
	e->v[e->i][0] != '<')
	{
		if (e->v[e->i][0] == '>')
		{
			e->i--;
			return (1);
		}
		e->i++;
	}
	return (0);
}
