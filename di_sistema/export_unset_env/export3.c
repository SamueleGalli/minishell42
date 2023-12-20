/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:32:41 by sgalli            #+#    #+#             */
/*   Updated: 2023/12/20 10:31:19 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	len_exp(char *str, t_env *e)
{
	int	i;
	int	k;

	k = 1;
	i = ft_strlen(str);
	if (e->v[e->i + 1] != NULL && e->v[e->i + 1][0] != 0 \
	&& (e->v[e->i + 1][0] == '\'' || e->v[e->i + 1][0] == '\"'))
	{
		e->i++;
		while (e->v[e->i][k] && e->v[e->i][k] != '\'' \
		&& e->v[e->i][k] != '\"')
		{
			i++;
			k++;
		}
		e->i--;
	}
	return (i);
}

void	alloc_mat_esp(char *d, t_env *e)
{
	int	i;
	int	j;

	j = 1;
	i = 0;
	while (e->v[e->i][i] != '\0')
	{
		d[i] = e->v[e->i][i];
		i++;
	}
	if (e->v[e->i + 1] != NULL && (e->v[e->i + 1][0] == '\'' || e->v[e->i
			+ 1][0] == '\"'))
	{
		while (e->v[e->i + 1] && e->v[e->i + 1][j] != '\'' && e->v[e->i
			+ 1][j] != '\"')
			d[i++] = e->v[e->i + 1][j++];
	}
	d[i] = '\0';
}

char	**new_tmp(t_env *e, char **tmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (e->env[j] != NULL)
	{
		if (j == e->count_exp)
		{
			update_env_v(e, 0, i, tmp);
			j++;
			i++;
		}
		else
		{
			tmp[i] = (char *)malloc(sizeof(char) * (ft_strlen(e->env[j]) + 1));
			alloc_mat(tmp[i], e->env[j]);
			i++;
			j++;
		}
	}
	return (cont_new_tmp(e, tmp, i));
}

void	apic_change(t_env *e, int i, char **tmp)
{
	int	j;

	j = 0;
	e->i--;
	e->indx = 0;
	tmp[i] = (char *)malloc(size(e) + 1);
	while (e->v[e->i][e->indx] != 0)
		tmp[i][j++] = e->v[e->i][e->indx++];
	if (e->v[e->i + 1] != NULL)
	{
		if (e->v[e->i + 1][0] == 34 || e->v[e->i + 1][0] == 39)
		{
			e->indx = 1;
			e->i++;
			while (e->v[e->i][e->indx] != 34 && e->v[e->i][e->indx] != 39
				&& e->v[e->i][e->indx] != 0)
				tmp[i][j++] = e->v[e->i][e->indx++];
		}
	}
	tmp[i][j] = '\0';
}

void	change_value(t_env *e, int i, char **tmp)
{
	if (e->v[e->i][0] == '\'' || e->v[e->i][0] == '\"')
		apic_change(e, i, tmp);
	else
	{
		tmp[i] = (char *)malloc(sizeof(char) * (ft_strlen(e->v[e->i]) + 1));
		alloc_mat(tmp[i], e->v[e->i]);
	}
}
