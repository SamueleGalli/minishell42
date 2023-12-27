/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 11:22:00 by sgalli            #+#    #+#             */
/*   Updated: 2023/12/27 13:33:14 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_digit(char *s, t_env *e)
{
	int	i;

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

int	init_nuller(t_env *e)
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

int	control_match(char *s)
{
	int		i;
	char	c;

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
