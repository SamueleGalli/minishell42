/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper10.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 12:50:12 by sgalli            #+#    #+#             */
/*   Updated: 2023/12/27 13:32:12 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_no_quote(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '\'' || s[i] == '\"')
		i++;
	while (s[i] != 0 && s[i] != '\'' && s[i] != '\"')
		printf("%c", s[i++]);
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

int	single_error(t_env *e)
{
	if (valid_redp(e, e->i_copy) == 1 || e->v[0][0] == '|')
	{
		if (e->v[0][0] == '|')
			printf("bash: syntax error near unexpected token `|'\n");
		else
			printf("bash: syntax error near unexpected token `newline'\n");
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

int	cont_last_check(t_env *e)
{
	if (e->v[e->i_copy][0] == '|' || valid_redp(e, e->i_copy) == 1)
	{
		if ((e->v[e->i_copy][1] != 0 && (e->v[e->i_copy][1] == '>' \
		|| e->v[e->i_copy][1] == '<')) || e->v[e->i_copy][0] == '|')
			printf("bash: syntax error near unexpected token `%s'\n",
				e->v[e->i_copy]);
		else
			printf("bash: syntax error near unexpected token `newline'\n");
		e->exit_code = 2;
		e->is_valid = 1;
		e->exit = 1;
		return (1);
	}
	return (0);
}
