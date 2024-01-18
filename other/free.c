/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:36:13 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/18 13:19:21 by sgalli           ###   ########.fr       */
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

void	exiting_d(t_env *e)
{
	if (e->path != NULL)
		free(e->path);
	if (e->p != NULL)
		free(e->p);
	if (e->mat_flag != NULL)
		free_table(e->mat_flag);
	if (e->env != NULL)
		free_table(e->env);
	if (e->t != NULL)
		free_table(e->t);
	free(e);
	exit(0);
}
