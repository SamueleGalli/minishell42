/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:12:38 by sgalli            #+#    #+#             */
/*   Updated: 2024/03/23 11:42:27 by sgalli           ###   ########.fr       */
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
	}
	else if (sig == SIGQUIT)
	{
		printf("Quit\n");
		g_code = 131;
	}
}

void	handle_signal_c(int sig)
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
	signal(SIGINT, &handle_signal_c);
	signal(SIGQUIT, SIG_IGN);
	if (g_code == 130)
	{

		e->exit_code = g_code;
		g_code = 0;
	}
	else if (g_code == 131)
	{
		e->exit = g_code;
		g_code = 0;
	}
}

void	singal_fork(t_env *e)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGQUIT, &handle_signal);
	signal(SIGINT, &handle_signal);
	if (g_code == 130)
	{
		e->exit_code = g_code;
		g_code = 0;
	}
	else if (g_code == 131)
	{
		e->exit = g_code;
		g_code = 0;
	}
}
