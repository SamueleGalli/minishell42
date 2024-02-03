/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:36:53 by sgalli            #+#    #+#             */
/*   Updated: 2024/02/03 11:11:50 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_i(t_env *e)
{
	if (e->v[e->i] != 0)
	{
		if (e->v[e->i][0] == '|' || e->v[e->i][0] == '<' || \
		e->v[e->i][0] == '>')
		{
			e->i++;
			return ;
		}
		else
		{
			while (e->v[e->i] != NULL && e->v[e->i][0] != '|' \
			&& e->v[e->i][0] != '<' && e->v[e->i][0] != '>')
				e->i++;
		}
	}
}

void	error(t_env *e)
{
	if (e->v[e->i][0] == '$' && e->v[e->i][1] == '?')
		printf("%d: command not found\n", e->exit_code);
	else
	{
		print_no_n(e->v[e->i]);
		if (e->v[e->i + 1] != NULL && e->v[e->i + 1][0] == '$' \
		&& e->v[e->i + 1][1] != '?' && e->v[e->i + 1][1] != 0)
		{
			e->i++;
			if (is_empty_variable(e, 0, 0) == 0)
			{
				e->exit_code = 0;
				e->exit = 1;
				return ;
			}
			typing(e);
			return ;
		}
	}
	e->exit_code = 127;
	e->exit = 1;
}

int	compare(char *s1, char *s2)
{
	int	j;

	j = 0;
	while (s1[j] != 0 && s2[j] != 0)
	{
		if (s1[j] != s2[j])
			return (0);
		j++;
	}
	if (s1[j] == 0 && s2[j] == 0)
		return (1);
	return (0);
}

int	empty(t_env *e)
{
	int	j;

	j = 0;
	while (e->v[e->i][j] != '\0')
	{
		if (e->v[e->i][j] != ' ' && e->v[e->i][j] != '\t')
			return (1);
		j++;
	}
	return (0);
}

int	ft_strnum(int i)
{
	int	c;

	c = 0;
	if (i == 0)
		return (1);
	while (i != 0)
	{
		i = i / 10;
		c++;
	}
	return (c);
}
