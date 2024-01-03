/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 10:36:03 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/03 11:42:40 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	show_history(void)
{
	int			j;
	HIST_ENTRY	**entry;

	entry = history_list();
	j = 0;
	if (entry != NULL)
	{
		while (entry[j] != NULL)
		{
			printf("%d %s\n", j + 1, entry[j]->line);
			j++;
		}
	}
}
