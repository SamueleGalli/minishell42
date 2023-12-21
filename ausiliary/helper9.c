/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper9.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 11:40:57 by sgalli            #+#    #+#             */
/*   Updated: 2023/12/21 13:01:56 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_tilde(char *s, int i)
{
	while (s[i] != 0)
		i++;
	return (i);
}

void	tilde_or_not(t_env *e, char *tmp)
{
	if (tmp[0] == '~')
	{
		go_root(e, 0);
		return ;
	}
	else if (chdir(tmp) == -1)
	{
		e->exit_code = 1;
		e->exit = 1;
		printf("bash: cd: %s: No such file or directory\n", tmp);
	}
}

int	while_last_null(t_env *e, int i)
{
	i++;
	while (e->v[i] != 0 && (e->v[i][0] == '|' || e->v[i][0] == '<' \
		|| e->v[i][0] == '>'))
			i++;
	if (e->v[i] == 0)
		i--;
	if (e->v[i] != NULL && (e->v[i][0] == 34 \
	|| e->v[i][0] == 39))
	{
		e->exit = 1;
		e->exit_code = 127;
		print_no_quote(e->v[i]);
		printf(": command not found\n");
		return (1);
	}
	if (e->v[i][0] == '>' || e->v[i][0] == '<' || e->v[i][0] == '|')
		printf("bash: syntax error near unexpected token `%s'\n", e->v[i]);
	e->exit = 1;
	e->exit_code = 2;
	return (1);
}

int	cont_while_null(t_env *e, int i)
{
	if (e->v[i][0] == '<' && e->v[i][1] == '|')
	{
		printf("bash: syntax error near unexpected token `|'\n");
		e->exit = 1;
		e->exit_code = 2;
		return (1);
	}
	if (e->v[i][0] == '>' || e->v[i][0] == '|' || e->v[i][0] == '|')
		return (while_last_null(e, i));
	return (0);
}

int	check_while_null(t_env *e, int i)
{
	i = e->i;
	while (e->v[i][0] != 0 && e->v[i][0] != '|' && e->v[i][0] != '<' \
		&& e->v[i][0] != '>')
		i++;
	if (e->v[i][0] == '|' && e->v[i + 1] == 0)
	{
		printf("bash: syntax error near unexpected token `|'\n");
		e->exit = 1;
		e->exit_code = 2;
		return (1);
	}
	else if ((e->v[i][0] == '<'  || e->v[i][0] == '>' ) && e->v[i + 1] == 0)
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		e->exit_code = 2;
		return (1);
	}
	return (cont_while_null(e, i));
}
