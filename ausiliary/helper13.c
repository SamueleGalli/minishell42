/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper13.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 11:45:20 by sgalli            #+#    #+#             */
/*   Updated: 2023/12/27 12:50:22 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			return (1);
	}
	return (3);
}
