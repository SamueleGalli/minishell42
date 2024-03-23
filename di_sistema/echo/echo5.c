/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 12:58:25 by sgalli            #+#    #+#             */
/*   Updated: 2024/03/23 13:05:13 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	close_quote_single(t_env *e, int i, int j)
{
	while (e->v[j][i] != 0 && e->v[j][i] != '\'')
	{
		if (e->v[j][i] == '\"')
		{
			printf("invalid quote");
			return (0);
		}
		i++;
	}
	if (e->v[j][i] != 0 && e->v[j][i] == '\'')
		return (1);
	else
	{
		printf("invalid quote");
		return (0);
	}
}

int	close_quote_double(t_env *e, int i, int j)
{
	while (e->v[j][i] != 0 && e->v[j][i] != '\"')
	{
		if (e->v[j][i] == '\'')
		{
			printf("invalid quote");
			return (0);
		}
		i++;
	}
	if (e->v[j][i] != 0 && e->v[j][i] == '\"')
		return (1);
	else
	{
		printf("invalid quote");
		return (0);
	}
}
