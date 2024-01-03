/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 10:43:05 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/03 11:41:26 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	get_var(t_env *e, int i, int j)
{
	e->j = 0;
	e->indx = 0;
	while (e->env[e->j] != NULL)
	{
		i = mini_get_var(e, i, j);
		if (i == -1)
			return ;
		e->j++;
	}
}

int	get_var_quote(t_env *e, int j, int iter, int i)
{
	while (e->env[++iter] != NULL)
	{
		while (e->v[j][e->word + 1] == e->env[iter][i])
		{
			i++;
			e->word++;
		}
		if (e->env[iter][i] == '=' && (e->v[j][e->word + 1] == ' ' \
		|| e->v[j][e->word + 1] == 34 || e->v[j][e->word + 1] == '$' \
		|| e->v[j][e->word + 1] == 0))
		{
			printf_env(e, iter);
			if (e->v[j + 1] != NULL)
				printf(" ");
			return (0);
		}
		else
		{
			e->word = 0;
			i = 0;
		}
	}
	return (1);
}

void	check_quote(t_env *e, int j)
{
	e->word = 1;
	if (check_closure(e->v[j]) == 1)
		print_str(e->v[j], 0);
	else if (e->v[j][0] == 39)
	{
		while (e->v[j][e->word] != 39)
			printf("%c", e->v[j][e->word++]);
	}
	else
	{
		while (e->v[j][e->word] != 34)
		{
			if (e->v[j][e->word] != '\0' && e->v[j][e->word + 1] != '\0' \
		&& e->v[j][e->word] == '$' && e->v[j][e->word + 1] != ' ' && \
		e->v[j][e->word + 1] != 34)
				bridge(e, j);
			else
				printf("%c", e->v[j][e->word++]);
		}
	}
}

void	mini_while(t_env *e)
{
	int	i;

	i = e->i;
	if (compare(e->v[i], "-n") == 1)
		return ;
	while (e->v[i] != 0 && e->v[i][0] != '|' && e->v[i][0] != '<' && \
	e->v[i][0] != '>')
	{
		if (e->v[i][0] == 34 || e->v[i][0] == 39)
		{
			check_quote(e, i);
			if (e->v[i + 1] != NULL)
				printf(" ");
		}
		else
			writer(e, i);
		i++;
	}
	print_red(e);
	e->exit_code = 0;
}

void	writeme(t_env *e)
{
	if ((compare(e->v[e->i], "echo") == 1 || compare(e->v[e->i], "echo ") == 1) \
	&& (e->v[e->i + 1] != NULL))
	{
		if (compare(e->v[e->i + 1], "-n ") == 1)
		{
			e->i = e->i + 2;
			mini_while(e);
		}
		else
		{
			e->i++;
			mini_while(e);
			if (compare(e->v[e->i], "-n") != 1 && e->v[e->i] != NULL)
				printf("\n");
		}
		return ;
	}
	else if (compare(e->v[e->i], "echo") == 1 && e->v[e->i + 1] == NULL)
	{
		e->i++;
		printf("\n");
	}
	else
		directory(e);
}
