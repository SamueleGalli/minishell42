/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:41:45 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/02 16:55:21 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	continuing_minor_double(t_env *e, char *s, pid_t pid)
{
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
		continue_heredoc(e, s);
	else
		waitpid(pid, NULL, 0);
	free(s);
}
