/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:36:41 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/03 11:36:43 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_builtin(t_env *e)
{
	if (compare(e->v[e->i], "echo") == 1 || compare(e->v[e->i], "echo ") == 1)
		return (1);
	else if (compare(e->v[e->i], "cd") == 1)
		return (1);
	else if (compare(e->v[e->i], "env") == 1)
		return (1);
	else if (compare(e->v[e->i], "export") == 1)
		return (1);
	else if (compare(e->v[e->i], "unset") == 1)
		return (1);
	else if (compare(e->v[e->i], "exit") == 1)
		return (1);
	else if (compare(e->v[e->i], "pwd") == 1)
		return (1);
	else
		return (0);
}

void	check_built(char *s, int i, t_env *e)
{
	while (s[i] != '|' && s[i] != '\0')
		i++;
	if (s[i] == '|')
		e->space = 1;
}
