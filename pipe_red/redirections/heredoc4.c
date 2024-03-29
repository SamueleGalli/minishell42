/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 12:01:40 by sgalli            #+#    #+#             */
/*   Updated: 2024/03/29 13:16:02 by sgalli           ###   ########.fr       */
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

void	writing_here(t_env *e)
{
	int	i;

	i = 0;
	close(e->pipefd[0]);
	while (e->here_p[i] != 0)
	{
		write(e->pipefd[1], &e->here_p[i], 1);
		i++;
	}
	close(e->pipefd[1]);
}

int	redir_file(t_env *e)
{
	int	i;

	i = e->i;
	while (e->v[i] != 0)
	{
		if (e->v[i][0] == '>')
			return (1);
		i++;
	}
	return (0);
}
