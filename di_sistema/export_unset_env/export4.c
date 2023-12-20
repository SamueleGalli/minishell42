/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 10:18:01 by sgalli            #+#    #+#             */
/*   Updated: 2023/12/20 12:12:08 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**cont_new_tmp(t_env *e, char **tmp, int i)
{
	if (e->count_exp != -1)
	{
		e->count_exp = -1;
		tmp[i] = NULL;
		return (tmp);
	}
	tmp[i] = (char *)malloc(sizeof(char) * (len_exp(e->v[e->i], e) + 1));
	alloc_mat_esp(tmp[i], e);
	i++;
	tmp[i] = NULL;
	return (tmp);
}
