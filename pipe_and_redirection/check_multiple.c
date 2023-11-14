/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_multiple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:26:37 by sgalli            #+#    #+#             */
/*   Updated: 2023/11/14 13:00:07 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_multiple(t_env *e)
{
	int	i;

	i = e->i;
	while (e->v[i] != NULL)
	{
		if (e->v[i][0] == '>')
			return (0);
		i++;
	}
	return (1);
}
//echo 42 < file1 | cat | wc -l
//devo eseguore la pipe usando il valore prima del <

void	in_pipe(t_env *e)
{
	(void)e;
}
