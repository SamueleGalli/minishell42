/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:44:56 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/16 12:53:37 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	execve_while(t_env *e, int i, int exist, int check)
{
	while (e->v[i] != NULL && e->v[i][0] != '|' && e->v[i][0] != '>'
		&& e->v[i][0] != '<')
	{
		if (exist == 1 && check == 0)
			printf(" ");
		print_no_quote(e->v[i++], exist);
		check = 0;
	}
	if (exist == 1)
	{
		printf("\n");
		exiting(e, e->exit_code);
	}
	return (i);
}

int	cont_print_red(t_env *e, int i, int exist)
{
	int	check;

	check = 0;
	if (i > e->i && e->v[i][0] != '>')
	{
		printf(" ");
		check = 1;
	}
	i += 2;
	if (e->v[i] != NULL)
		i = execve_while(e, i, exist, check);
	else
	{
		printf("\n");
		exiting(e, e->exit_code);
	}
	return (i);
}
