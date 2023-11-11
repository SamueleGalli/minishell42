/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:22:39 by sgalli            #+#    #+#             */
/*   Updated: 2023/10/25 15:22:46 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// conta la dimensione di un stringa e della successiva saltndo ' e "
int	size(t_env *e)
{
	e->indx = 0;
	e->count = 0;
	while (e->v[e->i][e->indx] != 0)
	{
		e->count++;
		e->indx++;
	}
	if (e->v[e->i + 1] != NULL)
	{
		if (e->v[e->i + 1][0] == 34 || e->v[e->i + 1][0] == 39)
		{
			e->i++;
			e->indx = 1;
			while (e->v[e->i][e->indx] != 34 && \
			e->v[e->i][e->indx] != 39 && e->v[e->i][e->indx] != 0)
			{
				e->count++;
				e->indx++;
			}
			e->i--;
		}
	}
	e->indx = 0;
	return (e->count);
}

char	*mini_strcat(char *d, const char *s)
{
	int	i;
	int	k;

	k = 0;
	i = strcom(d, 0);
	while (s[k] != '\0' && s[k] != ' ')
	{
		if (s[k] == 34 || s[k] == 39 || s[k] == '<' || s[k] == '>')
			k++;
		else
			d[i++] = s[k++];
	}
	d[i] = '\0';
	return (d);
}

int	strcom(char *s, int e)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (s == NULL)
		return (0);
	if (s[0] != '\0' && s[1] != '\0')
	{
		if (s[0] == '$' && s[1] == '?')
			return (ft_strnum(e));
	}
	while (s[j] != 0)
	{
		if (s[j] == 34 || s[j] == 39)
			j++;
		else
		{
			i++;
			j++;
		}
	}
	return (i);
}

int	size_mat(char **t)
{
	int	i;

	i = 0;
	while (t[i] != NULL)
		i++;
	return (i + 1);
}

char	**alloc_tmp(t_env *e, char **tmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (e->env[j] != NULL)
	{
		if (j == e->ex)
			change_value(e, i, tmp);
		else
		{
			tmp[i] = (char *)malloc(sizeof(char) * \
			(ft_strlen(e->env[j]) + 1));
			alloc_mat(tmp[i], e->env[j]);
		}
		i++;
		j++;
	}
	tmp[i] = NULL;
	return (tmp);
}
