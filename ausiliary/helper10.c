/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper10.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 12:50:12 by sgalli            #+#    #+#             */
/*   Updated: 2023/12/22 11:50:22 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void print_no_quote(char *s)
{
	int i;

	i = 0;
	if (s[i] == '\'' || s[i] == '\"')
		i++;
	while (s[i] != 0 && s[i] != '\'' && s[i] != '\"')
		printf("%c", s[i++]);
}

void switch_case(t_env *e, int j)
{
	printf("bash: syntax error near unexpected token `%c", e->v[e->i_copy][j]);
	j++;
	while (j != j + 1)
	{
		if (e->v[e->i_copy][j] != e->v[e->i_copy][j - 1])
		{
			printf("%c", e->v[e->i_copy][j]);
			break;
		}
		printf("%c", e->v[e->i_copy][j]);
		j++;
	}
	printf("\'\n");
}

int mutiple_equal(t_env *e)
{
	int j;

	j = 0;
	if (e->v[e->i_copy][j + 1] != 0 && \
	e->v[e->i_copy][j + 1] == e->v[e->i_copy][j])
	{
		j++;
		while ((e->v[e->i_copy][j] == '<' || e->v[e->i_copy][j] == '>'))
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

int single_error(t_env *e)
{
	if (e->v[0][0] == '|')
	{
		printf("bash: syntax error near unexpected token `|'\n");
		e->exit = 1;
		e->exit_code = 2;
		return (1);
	}
	else if (e->v[0][1] == ' ')
	{
		printf(" :command not found\n");
		e->exit_code = 127;
		return (1);
	}
	return (0);
}

int there_is_red(char *s)
{
	int i;

	i = 0;
	if (s[i] != 0)
	{
		if (s[i] != '<' || s[i] != '>')
			return (0);
		else if ((s[i + 1] == 0) || (s[i + 1] != 0 && s[i] == s[i + 1] && s[i + 2] == 0))
			return (1);
		else
			return (0);
	}
	return (0);
}