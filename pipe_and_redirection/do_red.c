/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_red.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 11:25:35 by sgalli            #+#    #+#             */
/*   Updated: 2023/11/21 10:30:13 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	last_check(t_env *e)
{
	e->check = e->i;
	if (e->v[e->i] == NULL)
		return ;
	else if (e->v[e->i][0] == '|')
	{
		e->i++;
		while (e->v[e->i] != NULL && e->v[e->i][0] != '|' && \
		e->v[e->i][0] != '<' && e->v[e->i][0] != '>')
			e->i++;
		if (e->v[e->i] == NULL)
			return ;
		else if (e->v[e->i][0] == '|')
			e->i = e->check;
		else if (e->v[e->i][0] == '>')
		{
			e->i = e->check + 1;
			e->do_redir = 1;
		}
	}
}

void	initialize_red(t_env *e)
{
	e->in_red = 0;
	e->out_red = 0;
	/*if (e->v[0][0] != '>' && e->v[0][0] != '<')
	{
		e->i = e->start_red;
		single_major_mult_redirect(e);
		update_redir(e);
	}*/
}

void	do_redir(t_env *e)
{
	initialize_red(e);
	while (e->v[e->i] != NULL && e->v[e->i][0] != '|')
	{
		while (e->v[e->i][0] != '<' && e->v[e->i][0] != '>')
			e->i++;
		if ((e->v[e->i][1] != '>') && (search_mult_arrows(e, "< ") == 1
				|| search_mult_arrows(e, "> ") == 1 || search_mult_arrows(e,
					"<") == 1 || search_mult_arrows(e, ">") == 1))
			redirect_mult_single(e);
		else if (search_mult_arrows(e, ">> ") == 1 || search_mult_arrows(e,
				">>") == 1)
			redirect_mult_double(e);
		if (e->do_redir == 1)
			execve_redir(e);
		update_redir(e);
		last_check(e);
	}
	if (e->in_red > 0 && e->out_red > 0)
		last_file(e);
}
