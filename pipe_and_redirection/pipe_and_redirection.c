/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 16:33:21 by sgalli            #+#    #+#             */
/*   Updated: 2023/11/10 18:44:00 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//cat < file1 | grep 1 > file2 | wc -l

int	pipe_or_redir(t_env *e)
{
	int	i;

	i = e->i;
	while (e->v[i][0] != '|' && e->v[i][0] != '<' && e->v[i][0] != '>')
	{
		i++;
		if (e->v[i] == NULL)
			return (0);
	}
	if (e->v[i][0] == '|')
		return (2);
	else
	{
		e->i = i;
		return (1);
	}
}

void	forking(t_env *e)
{
	if (e->v[e->i][0] == '|')
		e->i++;
	other_redir(e);
	define_redir(e);
}

void	do_pipe(t_env *e)
{
	e->c_pipe = 0;
	e->p_i = 0;
	count_pipe(e);
	while (e->p_i < e->c_pipe)
	{
		if (pipe(e->pipefd) == -1)
		{
			perror("pipe");
			exiting(e, 1);
		}
		forking(e);
		e->p_i++;
		update_pipe(e);
		if (e->v[e->i] == NULL)
			return ;
		if (e->v[e->i][0] == '>' || e->v[e->i][0] == '<')
		{
			find_first_command(e);
			return ;
		}
	}
	if (e->define_pipe == 1)
		parent2(e);
}

void	do_redir(t_env *e)
{
	while (e->v[e->i] != NULL && e->v[e->i][0] != '|')
	{
		while (e->v[e->i][0] != '<' && e->v[e->i][0] != '>')
			e->i++;
		if ((e->v[e->i][1] != '>') && (search_mult_arrows(e, "< ") == 1 \
	|| search_mult_arrows(e, "> ") == 1 || search_mult_arrows(e, "<") == 1 \
	|| search_mult_arrows(e, ">") == 1))
			redirect_mult_single(e);
		else if (search_mult_arrows(e, ">> ") == 1 || \
	search_mult_arrows(e, ">>") == 1)
			redirect_mult_double(e);
		update_redir(e);
	}
	if (e->in_red > 0 && e->out_red > 0)
		last_file(e);
}

void	pipe_and_redirection(t_env *e)
{
	e->in_red = 0;
	e->out_red = 0;
	while (e->v[e->i] != NULL && e->exit == 0)
	{
		if (pipe_or_redir(e) == 1)
			do_redir(e);
		else if (pipe_or_redir(e) == 2)
		{
			do_pipe(e);
			e->p_i = 0;
		}
		else
			break ;
	}
	dup2(e->stdin, STDIN_FILENO);
	close(e->stdin);
	dup2(e->stdout, STDOUT_FILENO);
	close(e->stdout);
}
