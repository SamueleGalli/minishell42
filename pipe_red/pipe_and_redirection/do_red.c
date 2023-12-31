/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_red.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 11:25:35 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/08 13:06:56 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_last_check(t_env *e)
{
	if (e->v[e->i] == NULL)
	{
		e->i = e->check;
		return ;
	}
	else if (e->v[e->i][0] == '|')
		e->i = e->check;
	else if (e->v[e->i][0] == '>')
	{
		e->i = e->check + 1;
		e->do_redir = 1;
	}
	else
	{
		e->i = e->check;
		e->i++;
		e->i_tmp = e->i;
	}
}

void	last_check(t_env *e)
{
	e->check = e->i;
	if (e->v[e->i] == NULL)
		return ;
	else if (e->v[e->i][0] == '|')
	{
		e->i++;
		while (e->v[e->i] != NULL && e->v[e->i][0] != '|'
			&& e->v[e->i][0] != '<' && e->v[e->i][0] != '>')
			e->i++;
		check_last_check(e);
	}
}

void	initialize_red(t_env *e)
{
	int	i;

	i = 0;
	e->in_red = 0;
	e->check_input = -1;
	e->out_red = 0;
	check_first_input(e);
	if (e->v[0][0] != '>' && e->v[0][0] != '<')
	{
		while (e->v[i][0] != '>' && e->v[i][0] != '<')
			i++;
		if (e->v[i][0] == '<')
			return ;
		e->i = e->start_red;
		single_major_mult_redirect(e);
		update_redir(e);
	}
}

void	red_type(t_env *e)
{
	if ((e->v[e->i][1] != '>') && (search_mult_arrows(e, "< ") == 1
	|| search_mult_arrows(e, "> ") == 1 || search_mult_arrows(e,
	"<") == 1 || search_mult_arrows(e, ">") == 1))
		redirect_mult_single(e);
	else if (search_mult_arrows(e, ">> ") == 1 || search_mult_arrows(e, \
	">>") == 1)
		redirect_mult_double(e);
	else if (compare(e->v[index_v_arrows(e, "<<")], "<<") == 1 \
	&& e->v[index_v_arrows(e, "<<") + 1] != NULL)
		double_minor_redirect(e);
}

int	do_redir(t_env *e)
{
	initialize_red(e);
	while (e->v[e->i] != NULL && e->v[e->i][0] != '|')
	{
		while (e->v[e->i][0] != '<' && e->v[e->i][0] != '>')
			e->i++;
		red_type(e);
		if (e->do_redir == 1)
			execve_redir(e);
		if (update_redir(e) == 0)
			return (0);
		e->i_tmp = e->i;
		last_check(e);
	}
	if (e->in_red > 0 && e->out_red > 0)
		last_file(e);
	return (1);
}
