/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 12:01:40 by sgalli            #+#    #+#             */
/*   Updated: 2024/02/03 13:35:59 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_here(t_env *e, char *line)
{
	if (line == NULL)
	{
		if (e->buffer != NULL)
		{
			free(e->buffer);
			e->buffer = NULL;
		}
		if (line != NULL)
		{
			free(line);
			line = NULL;
		}
		return (2);
	}
	return (0);
}

int	final_here(t_env *e, int i)
{
	if (e->delim[i] == NULL)
	{
		redirect_double_arrows(e, e->buffer);
		return (1);
	}
	else
	{
		free(e->buffer);
		e->buffer = NULL;
	}
	return (0);
}
