/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:20:16 by sgalli            #+#    #+#             */
/*   Updated: 2023/11/10 12:09:59 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cont_invalid_cmd(t_env *e, int i)
{
	while (e->v[i] != NULL)
	{
		if (e->v[i][0] == '|' && (e->v[i + 1] == NULL \
		|| e->v[i + 1][0] == '\0'))
		{
			printf("error parse error near `|'\n");
			e->exit = 1;
			e->exit_code = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_builtin(t_env *e)
{
	if (compare(e->v[e->i], "echo") == 1 || compare(e->v[e->i], "echo ") == 1)
		return (1);
	else if (compare(e->v[e->i], "cd") == 1)
		return (1);
	else if (compare(e->v[e->i], "env") == 1)
		return (1);
	else if (compare(e->v[e->i], "export") == 1)
		return (1);
	else if (compare(e->v[e->i], "unset") == 1)
		return (1);
	else if (compare(e->v[e->i], "exit") == 1)
		return (1);
	else if (compare(e->v[e->i], "pwd") == 1)
		return (1);
	else
		return (0);
}

void	check_built(char *s, int i, t_env *e)
{
	while (s[i] != '|' && s[i] != '\0')
		i++;
	if (s[i] == '|')
		e->space = 1;
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_strlen_red(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}
