/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:57:12 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/23 10:21:47 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	last_check_val(t_env *e, int j)
{
	if ((e->v[e->i_copy][j] == 0 && e->v[e->i_copy][j - 1] == '>')
		|| e->v[e->i_copy][j] == '>')
	{
		e->exit = 1;
		e->exit_code = 2;
		printf("bash: syntax error near unexpected token `>'\n");
		return (1);
	}
	return (0);
}

void	switch_case(t_env *e, int j)
{
	int	i;

	i = 0;
	printf("bash: syntax error near unexpected token `%c", e->v[e->i_copy][j]);
	j++;
	while (j != j + 1)
	{
		if (e->v[e->i_copy][j] != e->v[e->i_copy][j - 1])
		{
			printf("%c", e->v[e->i_copy][j]);
			break ;
		}
		printf("%c", e->v[e->i_copy][j]);
		i++;
		if (i == 2)
			break ;
		j++;
	}
	printf("\'\n");
}

int	mutiple_equal(t_env *e)
{
	int	j;

	j = 0;
	if (e->v[e->i_copy][j + 1] != 0 && e->v[e->i_copy][j
		+ 1] == e->v[e->i_copy][j])
	{
		j++;
		while (e->v[e->i_copy][j] == '<' || e->v[e->i_copy][j] == '>')
		{
			if (e->v[e->i_copy][j] != e->v[e->i_copy][j - 1])
				break ;
			else if (j == 3)
			{
				switch_case(e, j);
				return (1);
			}
			j++;
		}
	}
	return (last_check_val(e, j));
}

int	valid_redp(t_env *e, int i)
{
	if (e->v[i][0] == '>' || e->v[i][0] == '<')
	{
		if (e->v[i][1] != 0)
		{
			if (e->v[i][1] == '>' || e->v[i][1] == '<')
			{
				if (e->v[i][2] != 0)
					return (0);
				else
					return (1);
			}
			else
				return (0);
		}
		else
			return (0);
	}
	return (3);
}

void	pipe_error(t_env *e)
{
	if (e->v[e->i_copy] != NULL && e->v[e->i_copy + 1] != NULL && \
	e->v[e->i_copy][0] == '|' && (e->v[e->i_copy + 1][0] == '\'' || \
	e->v[e->i_copy + 1][0] == '\"'))
	{
		printf("command not found\n");
		e->exit_code = 127;
		e->is_valid = 1;
		return ;
	}
}
