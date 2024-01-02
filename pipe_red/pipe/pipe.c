/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:29:43 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/02 16:17:53 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pipe_com(t_env *e)
{
	execve(e->s, e->mat_flag, e->env);
	perror("execve");
	exiting(e, 0);
}

void	piping(t_env *e)
{
	e->exit_code = 0;
	multiple_pipe(e);
	e->p_i = 0;
	dup2(e->stdin, STDIN_FILENO);
	close(e->stdin);
	dup2(e->stdout, STDOUT_FILENO);
	close(e->stdout);
}
