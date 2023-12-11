/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:12:48 by eraccane          #+#    #+#             */
/*   Updated: 2023/12/11 14:10:29 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	redirect_double(t_env *e)
{
	if ((compare(e->v[index_v_arrows(e, ">>")], ">>") == 1 \
			|| compare(e->v[index_v_arrows(e, ">> ")], ">> ") == 1) \
		&& e->v[index_v_arrows(e, ">>") + 1] != NULL)
		double_major_redirect(e);
	else if (compare(e->v[index_v_arrows(e, "<<")], "<<") == 1 \
			&& e->v[index_v_arrows(e, "<<") + 1] != NULL)
		double_minor_redirect(e);
	else
	{
		e->exit = 1;
		errno = EINVAL;
		perror("minishell: warning");
	}
}

void	redirect_single(t_env *e)
{
	if ((compare(e->v[index_v_arrows(e, ">")], ">") == 1 \
			|| compare(e->v[index_v_arrows(e, "> ")], "> ") == 1) \
		&& e->v[index_v_arrows(e, ">") + 1] != NULL)
		single_major_redirect(e);
	else if ((compare(e->v[index_v_arrows(e, "<")], "<") == 1 \
				|| compare(e->v[index_v_arrows(e, "< ")], "< ") == 1) \
			&& e->v[index_v_arrows(e, "<") + 1] != NULL)
		single_minor_redirect(e);
	else
	{
		e->exit = 1;
		errno = EINVAL;
		perror("minishell: warning");
	}
}

int	check_pid_red(pid_t pid)
{
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	else
		return (0);
}

void	init_heredoc(t_env *e)
{
	if (check_builtin(e) == 0 && compare(e->v[0], "cat") == 0)
	{
		e->i = 0;
		pathcmd(e);
		flag_matrix(e);
	}
	else
		e->s = NULL;
}

void	continue_heredoc(t_env *e, char *s)
{
	if (e->v[0][0] != '<')
	{
		init_heredoc(e);
		if (e->s != NULL)
		{
			if (e->c_path == 0 && access(e->s, X_OK) == 0)
				pipe_com(e);
			free(s);
		}
		else
		{
			if (compare(e->v[0], "cat") == 1)
				printf("%s", s);
			else
				variabletype(e);
		}
	}
	free(s);
	exiting(e, 1);
}
