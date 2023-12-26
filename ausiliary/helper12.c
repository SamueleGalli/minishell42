/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper12.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 11:28:01 by sgalli            #+#    #+#             */
/*   Updated: 2023/12/26 12:24:23 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_max_min(t_env *e)
{
	if (e->v[e->i + 1] != NULL)
	{
		if (ft_strlen(e->v[e->i + 1]) == 19 && e->v[e->i + 1][18] >= '8')
		{
			printf("bash: exit: %s: numeric argument required\n", e->v[e->i
				+ 1]);
			exiting(e, 2);
		}
		else if (ft_strlen(e->v[e->i + 1]) == 20 && e->v[e->i + 1][19] > '8')
		{
			printf("bash: exit: %s: numeric argument required\n", e->v[e->i
				+ 1]);
			exiting(e, 2);
		}
	}
}
