/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 09:27:45 by marvin            #+#    #+#             */
/*   Updated: 2023/12/12 12:40:53 by sgalli           ###   ########.fr       */
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
		if (e->v[i][0] == '<' || e->v[i][0] == '>' || e->v[i][1] == '>' \
		|| e->v[i][1] == '<')
			red_num++;
		i++;
	}
	return (red_num);
}

void	what_exit(t_env *e)
{
	if (e->v[e->i + 1] != NULL && ft_check_digit(e->v[e->i + 1]) == 1)
	{
		if (e->v[e->i + 2] != NULL)
		{
			e->exit_code = 1;
			printf("too many arguments\n");
			return ;
		}
		else if (ft_check_digit(e->v[e->i + 1]) == 1)
			e->exit_code = ft_atoi(e->v[e->i + 1]);
	}
	else
		e->exit_code = 2;
	exiting(e, e->exit_code);
}

void	type_cont(t_env *e)
{
	if (arrows_number(e) > 1)
	{
		multiple_redirect(e);
		return ;
	}
	if (compare(e->v[e->i], "exit") == 1 && e->exit != 1)
		what_exit(e);
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
