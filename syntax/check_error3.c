/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:44:45 by sgalli            #+#    #+#             */
/*   Updated: 2024/03/25 16:56:16 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	invalid_red(t_env *e, int i)
{
	while (e->v[i] != 0 && e->v[i][0] != '>' && \
	e->v[i][0] != '<')
	{
		i++;
	}
	if ((e->v[i] != 0 && e->v[i + 1] != 0) && (e->v[i + 1][0] == '>' || \
	e->v[i + 1][0] == '<'))
	{
		printf("syntax error near unexpected token `%s'\n", e->v[i + 1]);
		e->is_valid = 1;
		e->exit_code = 2;
		return (1);
	}
	return (0);
}
