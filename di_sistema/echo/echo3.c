/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 11:50:47 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/12 10:21:07 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	apice_var_quote(t_env *e, int j, int iter, int i)
{
	while (e->env[++iter] != NULL)
	{
		while (e->v[j][e->word] == e->env[iter][i])
		{
			i++;
			e->word++;
		}
		if (e->env[iter][i] == '=' && (e->v[j][e->word] == ' ' \
		|| e->v[j][e->word] == 34 || e->v[j][e->word] == '$' \
		|| e->v[j][e->word] == 0))
		{
			printf_env(e, iter);
			if (e->v[j + 1] != NULL)
				printf(" ");
			return ;
		}
		else
		{
			e->word = e->numb;
			i = 0;
		}
	}
	while (e->v[j][e->word] != 0 && e->v[j][e->word] != ' ' \
	&& e->v[j][e->word] != 34)
		e->word++;
}

void	print_str(char *s, int i)
{
	if (s == NULL)
		return ;
	while (s[i] != '\0')
		printf("%c", s[i++]);
}

int	control_match(char *s)
{
	int		i;
	char	c;

	i = 0;
	c = s[0];
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	check_closure(char *s)
{
	int	i;

	i = 1;
	if (control_match(s) == 1)
		return (0);
	while (s[i] != '\0' && s[i] != 34 && s[i] != 39)
		i++;
	if (s[i] == '\0')
		return (1);
	else if (s[i] != s[0])
		return (1);
	return (0);
}

void	print_red(t_env *e)
{
	int	i;

	i = e->i;
	while (e->v[i] != 0 && e->v[i][0] != '>' && e->v[i][0] != '<')
		i++;
	if (e->v[i] != 0 && e->v[i][0] == '<' && e->out_red == 0)
	{
		if (i > e->i)
			printf(" ");
		i += 2;
		if (e->v[i] != NULL)
		{
			while (e->v[i] != NULL && e->v[i][0] != '|' && e->v[i][0] != '>'
				&& e->v[i][0] != '<')
				print_no_quote(e->v[i++]);
		}
	}
	else
	{
		printf("\n");
		return ;
	}
	if (e->v[i] != NULL)
		return ;
	printf("\n");
}
