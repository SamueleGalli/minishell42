/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 11:22:00 by sgalli            #+#    #+#             */
/*   Updated: 2023/12/13 11:43:04 by sgalli           ###   ########.fr       */
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

int	check_validation(t_env *e)
{
	if (e->v[0][1] == ' ')
	{
		printf("command_not_found %c\n", e->v[0][1]);
		e->exit_code = 127;
		return (1);
	}
	else if (e->v[0][0] == '\'' && (e->v[0][1] == '>' || e->v[0][1] == '<'))
	{
		printf("command_not_found %c\n", e->v[0][1]);
		e->exit_code = 127;
		return (1);
	}
	return (0);
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
