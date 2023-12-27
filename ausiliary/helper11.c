/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper11.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 10:57:12 by sgalli            #+#    #+#             */
/*   Updated: 2023/12/27 12:29:49 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	last_check_val(t_env *e, int j)
{
	if ((e->v[e->i_copy][j] == 0 && e->v[e->i_copy][j - 1] == '>')
		|| e->v[e->i_copy][j] == '>')
	{
		e->exit = 1;
		e->exit_code = 2;
		printf("bash: syntax error near unexpected token `>'\n");
		return (1);
	}
	return (0);
}

void	single_export(t_env *e)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (e->env[i] != 0)
	{
		printf("declare -x ");
		while (e->env[i][j] != '=')
			printf("%c", e->env[i][j++]);
		printf("=\"");
		j++;
		while (e->env[i][j])
			printf("%c", e->env[i][j++]);
		printf("\"\n");
		i++;
		j = 0;
	}
	return ;
}

int	next_valid(char *s, t_env *e)
{
	if (compare(e->v[e->i], "export") == 1)
	{
		if (s == 0)
			return (0);
		else
		{
			if (s[0] == '|' || s[0] == '<' || s[0] == '>')
				return (0);
			else
				return (1);
		}
	}
	return (2);
}
