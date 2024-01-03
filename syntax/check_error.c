/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 11:22:00 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/03 11:43:35 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	dimension_validation(t_env *e)
{
	if (ft_strlen(e->v[e->i_copy]) >= 3 && (mutiple_equal(e) == 1))
	{
		e->exit_code = 2;
		e->is_valid = 1;
		return ;
	}
	else if (e->v[e->i_copy][1] != 0
		&& e->v[e->i_copy][1] != e->v[e->i_copy][0])
	{
		e->exit = 1;
		e->exit_code = 2;
		e->is_valid = 1;
		printf("bash: syntax error near unexpected token `%c'\n",
			e->v[e->i_copy][1]);
		return ;
	}
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

void	cont_check_validation(t_env *e)
{
	if (valid_redp(e, e->i_copy) == 0)
		dimension_validation(e);
	if ((e->v[e->i_copy][0] == '<' && e->v[e->i_copy][1] == '<' && \
	e->v[e->i_copy][2] == '<') || ((e->v[e->i_copy][0] == '>' || \
	e->v[e->i_copy][0] == '<') && e->v[e->i_copy][1] == 0 \
	&& e->v[e->i_copy + 1] == 0))
	{
		if (e->exit == 1 || e->is_valid == 1)
			return ;
		printf("bash: syntax error near unexpected token `newline'\n");
		e->exit = 1;
		e->is_valid = 1;
		e->exit_code = 2;
		return ;
	}
}

void	check_validation(t_env *e)
{
	e->i_copy = 0;
	if (single_error(e) == 1)
	{
		e->is_valid = 1;
		return ;
	}
	while (e->v[e->i_copy] != 0 && e->is_valid == 0)
	{
		if (e->v[e->i_copy][0] != 34 || e->v[e->i_copy][0] != 39)
			cont_check_validation(e);
		if (e->exit == 0 && e->v[e->i_copy + 1] == 0 && \
		(e->v[e->i_copy][0] == '|' \
		|| e->v[e->i_copy][0] == '<' || e->v[e->i_copy][0] == '>'))
		{
			if (cont_last_check(e) == 1)
				return ;
		}
		e->i_copy++;
	}
	return ;
}
