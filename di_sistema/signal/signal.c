/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:12:38 by sgalli            #+#    #+#             */
/*   Updated: 2024/03/28 15:15:54 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		g_code;

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
	signal(SIGINT, &handle_signal);
	signal(SIGQUIT, SIG_IGN);
	if (g_code == 130 && e->her == 0)
	{
		e->exit_code = g_code;
		g_code = 0;
	}
	else if (g_code == 131 && e->her == 0)
	{
		e->exit_code = g_code;
		g_code = 0;
		return ;
	}
	else if (g_code == 131 && e->her == 1)
	{
		e->exit_code = g_code;
		g_code = 0;
		exiting(e, 0);
	}
}

void	handle_signal_fork(int sig)
{
	if (sig == SIGINT)
	{
		g_code = 130;
		write(2, "\n", 1);
	}
	else if (sig == SIGQUIT)
	{
		g_code = 131;
		ft_putstr_fd("Quit\n", 2);
	}
}

void	handle_here(int sig)
{
	if (sig == SIGQUIT)
		g_code = 130;
}

void	singal_fork(void)
{
	signal(SIGINT, &handle_signal_fork);
	signal(SIGQUIT, &handle_signal_fork);
}
