/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 10:36:03 by sgalli            #+#    #+#             */
/*   Updated: 2023/10/27 12:13:15 by sgalli           ###   ########.fr       */
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
