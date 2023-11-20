/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_red.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 11:25:35 by sgalli            #+#    #+#             */
/*   Updated: 2023/11/20 13:26:43 by sgalli           ###   ########.fr       */
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
		else if (e->v[e->i][0] == '>' || e->v[e->i][0] == '<')
		{
			e->i = e->check + 1;
		}
	}
}

void	do_redir(t_env *e)
{
	e->in_red = 0;
	e->out_red = 0;
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
		update_redir(e);
		last_check(e);
	}
	if (e->in_red > 0 && e->out_red > 0)
		last_file(e);
}