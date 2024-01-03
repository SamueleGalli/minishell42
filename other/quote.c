/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:36:27 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/03 11:36:29 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_no_quote(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '\'' || s[i] == '\"')
		i++;
	while (s[i] != 0 && s[i] != '\'' && s[i] != '\"')
		printf("%c", s[i++]);
}

void	var_quote(t_env *e, int j, int iter, int i)
{
	e->word = 1;
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
			return ;
		}
		else
		{
			e->word = 1;
			i = 0;
		}
	}
}
