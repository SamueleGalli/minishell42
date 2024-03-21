/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 10:43:05 by sgalli            #+#    #+#             */
/*   Updated: 2024/03/21 11:22:27 by sgalli           ###   ########.fr       */
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
		if (close_quote(e, '\'', 1, j) == 0)
			return ;
		while (e->v[j][e->word] != 39)
			printf("%c", e->v[j][e->word++]);
	}
	else
	{
		if (close_quote(e, '\"', 1, j) == 0)
			return ;
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
	int	exist;

	i = e->i;
	exist = 0;
	if (e->v[e->i] == 0 || compare(e->v[i], "-n") == 1)
		return ;
	while (e->v[i] != 0 && e->v[i][0] != '|' && e->v[i][0] != '<' && \
	e->v[i][0] != '>')
	{
		exist = 1;
		i = short_echo(e, i);
		if (e->v[i] != NULL)
			i++;
	}
	if (e->pi_re == 1)
		print_red(e, exist);
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
			if (e->pi_re == 0)
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
