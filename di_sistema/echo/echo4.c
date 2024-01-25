/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:44:56 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/25 11:09:46 by sgalli           ###   ########.fr       */
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

int	short_echo(t_env *e, int i)
{
	if (e->v[i][0] == 34 || e->v[i][0] == 39)
	{
		check_quote(e, i);
		if (e->v[i + 1] != NULL)
			printf(" ");
	}
	else
		i = writer(e, i);
	return (i);
}

void	short_write(t_env *e, int j)
{
	if (e->v[j][e->word] == '$' && (e->v[j][e->word + 1] == 0 || e->v[j][e->word
			+ 1] == ' '))
		printf("%c", e->v[j][e->word++]);
	if (e->v[j][e->word] == '$' && ft_isalpha(e->v[j][e->word + 1]) == 0)
	{
		while (e->v[j][e->word] != 0)
			printf("%c", e->v[j][e->word++]);
	}
	while (e->v[j][e->word] != 0 && e->v[j][e->word] != '$')
		printf("%c", e->v[j][e->word++]);
}
