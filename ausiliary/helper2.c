/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:55:37 by sgalli            #+#    #+#             */
/*   Updated: 2023/11/08 19:08:51 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_table(char **s)
{
	int	i;

	i = 0;
	if (s == NULL || s[0] == NULL)
		return ;
	else
	{
		while (s[i] != NULL)
			free(s[i++]);
		free(s);
	}
}

void	exiting(t_env *e, int i)
{
	if (e->p != NULL)
		free(e->p);
	if (e->s != NULL)
		free(e->s);
	if (e->path != NULL)
		free(e->path);
	if (e->mat_flag != NULL)
		free_table(e->mat_flag);
	if (e->v != NULL)
		free_table(e->v);
	if (e->env != NULL)
		free_table(e->env);
	if (e->cmd != NULL)
		free(e->cmd);
	free(e);
	exit(i);
}

void	print_str(char *s, int i)
{
	if (s == NULL)
		return ;
	while (s[i] != '\0')
		printf("%c", s[i++]);
}

int	check_closure(char *s)
{
	int	i;

	i = 1;
	while (s[i] != '\0' && s[i] != 34 && s[i] != 39)
		i++;
	if (s[i] == '\0')
		return (1);
	else if (s[i] != s[0])
		return (1);
	return (0);
}

void	update_eword(t_env *e, int j)
{
	while (e->v[j][e->word] != 32 && e->v[j][e->word] != 34 &&
			e->v[j][e->word] != '$')
		e->word++;
}
