/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 12:23:00 by sgalli            #+#    #+#             */
/*   Updated: 2023/11/05 16:27:35 by sgalli           ###   ########.fr       */
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
	if (e->s != NULL)
		free(e->s);
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

int	invalid_cmd(t_env *e)
{
	int	i;

	i = 0;
	if (cont_invalid_cmd(e, i) == 1)
		return (1);
	while (e->v[i] != NULL && e->v[i][0] != '\0' && \
	e->v[i][0] != '|' && e->v[i][0] != '<' \
	&& e->v[i][0] != '>' && compare(e->v[i], "<<") == 0 && \
	compare(e->v[i], ">>") == 0)
		i++;
	if (e->v[i] == NULL)
		return (0);
	i++;
	if (e->v[i] == NULL)
		return (0);
	while (e->v[i][0] == '|' || e->v[i][0] == '<' || \
	e->v[i][0] == '>' || compare(e->v[i], "<<") == 1 || \
	compare(e->v[i], ">>") == 1)
	{
		printf("invalid syntax ");
		print_str(e->v[i], 0);
		printf("\n");
		return (1);
	}
	return (0);
}
