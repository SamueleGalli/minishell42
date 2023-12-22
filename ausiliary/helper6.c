/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 11:22:00 by sgalli            #+#    #+#             */
/*   Updated: 2023/12/22 12:05:38 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_check_digit(char *s, t_env *e)
{
	int i;

	i = 0;
	while (s[i] != 0)
	{
		if (s[i] == '-')
		{
			e->sign = -1;
			i++;
		}
		else if (s[i] == '+')
		{
			e->sign = 1;
			i++;
		}
		else if (s[i] == '\"')
			i++;
		else if ((s[i] >= '0' && s[i] <= '9') || s[i] == ' ')
			i++;
		else
			return (0);
	}
	return (1);
}

int init_nuller(t_env *e)
{
	e->output = 0;
	e->input = 0;
	e->s = NULL;
	if (e->cmd[0] == '\0')
	{
		e->v = NULL;
		return (0);
	}
	splitme(e);
	e->i = 0;
	e->exit = 0;
	return (1);
}

void cont_check_validation(t_env *e)
{
	if (e->v[e->i_copy + 1] == 0 && there_is_red(e->v[e->i_copy]) == 1)
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		e->exit_code = 2;
		e->is_valid = 1;
		return ;
	}
	else
	{
		if (check_red(e->v[e->i_copy]) == 1)
			if (ft_strlen(e->v[e->i_copy]) >= 3 && (mutiple_equal(e) == 1))
			{
				e->exit_code = 2;
				e->is_valid = 1;
				return ;
			}
	}
	check_while_null(e);
}

void check_validation(t_env *e)
{
	e->i_copy = 0;
	if (single_error(e) == 1)
	{
		e->is_valid = 1;	
		return ;
	}
	while (e->v[e->i_copy] != 0 && e->is_valid == 0)
	{
		if ((e->v[e->i_copy][0] == '\'' || e->v[e->i_copy][0] == '\"') && \
		(e->v[e->i_copy][1] == '>' || e->v[e->i_copy][1] == '<' ||\
		e->v[e->i_copy][1] == '|'))
		{
			print_no_quote(e->v[e->i_copy]);
			printf(": command not found\n");
			e->exit_code = 127;
			e->is_valid = 1;
		}
		else
			cont_check_validation(e);
		e->i_copy++;
	}
	return ;
}

int control_match(char *s)
{
	int i;
	char c;

	i = 0;
	c = s[0];
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}
