/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:36:46 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/26 13:17:22 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*alloc_s(char *buf)

{
	int		i;
	char	*t;

	if (buf == NULL)
		return (NULL);
	t = (char *)malloc(sizeof(char) * ft_strlen(buf) + 1);
	i = 0;
	while (buf[i] != 0)
	{
		t[i] = buf[i];
		i++;
	}
	t[i] = 0;
	return (t);
}

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

char	*alloc_file(t_env *e, char s)
{
	if (e->v[e->i] != NULL && e->v[e->i][0] == '>')
	{
		e->i++;
		return (e->v[e->i]);
	}
	while (e->v[e->i] != NULL)
	{
		if (e->v[e->i][0] == s)
		{
			e->i++;
			if (e->v[e->i + 1] == NULL || e->v[e->i + 1][0] == '>' || e->v[e->i
				+ 1][0] == '|')
				return (e->v[e->i]);
		}
		else if (e->v[e->i][0] == '<' || e->v[e->i][0] == '|')
			return (0);
		e->i++;
	}
	return (0);
}

int	alloc_str(t_env *e, int i, int c)
{
	int	size;

	while (e->env[e->j][e->i2] != 0)
	{
		while (e->env[e->j][e->i2] != 0 && e->env[e->j][e->i2] == ' ')
			e->i2++;
		size = size_env(e);
		e->t[c] = (char *)malloc(sizeof(char) * (size + 1));
		while (e->env[e->j][e->i2] != 0 && e->env[e->j][e->i2] != ' ')
			e->t[c][i++] = e->env[e->j][e->i2++];
		e->t[c][i] = 0;
		i = 0;
		c++;
	}
	return (c);
}

void	alloc_mat_space(char *d, char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		d[i] = s[i];
		i++;
	}
	d[i++] = ' ';
	d[i] = '\0';
}
