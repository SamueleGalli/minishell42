/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:26:37 by sgalli            #+#    #+#             */
/*   Updated: 2024/03/25 18:16:36 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	do_pipe(t_env *e)
{
	if (pipe(e->pipefd) == -1)
	{
		perror("pipe");
		exiting(e, 1);
	}
	if (e->v[e->i][0] == '|')
	{
		e->i++;
		e->tmp_i = e->i;
	}
	if (pipe_or_redir(e) == 1)
	{
		do_redir(e);
		return ;
	}
	control_pipe(e);
	execute_pipe(e);
	update_pipe(e);
}
