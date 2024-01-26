/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:12:38 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/26 10:38:02 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	g_code;

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_code = 130;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		rl_clear_history();
	}
}

void	singals(t_env *e)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &handle_signal);
	if (g_code == 130)
	{
		e->exit_code = g_code;
		g_code = 0;
	}
}
