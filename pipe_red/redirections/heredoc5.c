/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:31:35 by sgalli            #+#    #+#             */
/*   Updated: 2024/03/28 15:08:31 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
