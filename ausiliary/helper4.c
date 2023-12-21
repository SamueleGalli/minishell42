/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 12:23:00 by sgalli            #+#    #+#             */
/*   Updated: 2023/12/21 11:49:43 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	alloc_mat(char *d, char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
}

char	**exclude_env(t_env *e, char **tmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (e->env[i] != NULL)
	{
		if (i == e->r)
			i++;
		if (e->env[i] == NULL)
			break ;
		tmp[j] = (char *)malloc(sizeof(char) * (ft_strlen(e->env[i]) + 1));
		alloc_mat(tmp[j], e->env[i]);
		j++;
		i++;
	}
	tmp[j] = NULL;
	return (tmp);
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
	free(e);
	exit(0);
}

int	ft_strnum(int i)
{
	int	c;

	c = 0;
	if (i == 0)
		return (1);
	while (i != 0)
	{
		i = i / 10;
		c++;
	}
	return (c);
}
