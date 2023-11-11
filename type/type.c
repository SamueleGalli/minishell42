/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 09:27:45 by marvin            #+#    #+#             */
/*   Updated: 2023/11/09 17:01:57 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	arrows_number(t_env *e)
{
	int	i;
	int	red_num;

	i = 0;
	red_num = 0;
	while (e->v[i] != NULL)
	{
		if (compare(e->v[i], ">>") || compare(e->v[i], ">") || compare(e->v[i],
				"<<") || compare(e->v[i], "<") || compare(e->v[i], ">> ")
			|| compare(e->v[i], "> ") || compare(e->v[i], "<< ")
			|| compare(e->v[i], "< "))
			red_num++;
		i++;
	}
	return (red_num);
}

void	type_cont(t_env *e)
{
	if (arrows_number(e) > 1)
	{
		multiple_redirect(e);
		return ;
	}
	if (compare(e->v[e->i], "exit") == 1 && e->exit != 1)
		exiting(e, 0);
	else if (search_arrows(e, "< ") == 1 || search_arrows(e, "> ") == 1
		|| search_arrows(e, "<") == 1 || search_arrows(e, ">") == 1)
	{
		redirect_single(e);
		return ;
	}
	else if (search_arrows(e, "<< ") == 1 || search_arrows(e, ">> ") == 1
		|| search_arrows(e, "<<") == 1 || search_arrows(e, ">>") == 1)
	{
		redirect_double(e);
		return ;
	}
	else if (e->v != NULL && e->exit != 1)
		variabletype(e);
}
// 	m
/*
** NOTE - cercare se nel comando c'e < o > , << o >> per evitare di far
** eseguire comandi precedenti
** TODO - la stampa di echo entra dentro variabletype, evitare se ci sono arrows
** di eseguire il cmd
** TODO - da controllare se >... e a fine stringa (ovvero se ha lo spazio dopo)
** all'interno di e->v quando viene splittato

< file1 > file3
*/

void	typing(t_env *e)
{
	if (valid_pipe(e) == 1)
		return ;
	else if (search_pipe(e) == 1)
	{
		count_pipe(e);
		if (search_arrows(e, "< ") == 1 || search_arrows(e, "> ") == 1
			|| search_arrows(e, "<") == 1 || search_arrows(e, ">") == 1
			|| search_arrows(e, "<< ") == 1 || search_arrows(e, ">> ") == 1
			|| search_arrows(e, "<<") == 1 || search_arrows(e, ">>") == 1)
			pipe_and_redirection(e);
		else
			piping(e);
		e->exit = 1;
		return ;
	}
	else
		type_cont(e);
	return ;
}
