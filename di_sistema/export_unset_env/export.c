/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 10:37:55 by sgalli            #+#    #+#             */
/*   Updated: 2023/12/22 12:24:51 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exporapice(t_env *e, int i, int j)
{
	if (e->v[i + 1] != NULL)
	{
		if (e->v[i + 1][0] == 34 || e->v[i + 1][0] == 39)
		{
			i++;
			j++;
			while (e->v[i][j] != '\0')
			{
				if (e->v[i][j] == 34 || e->v[i][j] == 39)
				{
					if (e->v[i][0] == e->v[i][j])
						return (0);
				}
				j++;
			}
			return (1);
		}
	}
	return (0);
}

void	shortwhile(t_env *e)
{
	while (e->v[e->i][e->indx] != 0)
		e->env[e->r][e->iter++] = e->v[e->i][e->indx++];
	if (e->v[e->i + 1] != NULL)
	{
		if (e->v[e->i + 1][0] == 34 || e->v[e->i + 1][0] == 39)
		{
			e->indx = 1;
			e->i++;
			while (e->v[e->i][e->indx] != 34 && e->v[e->i][e->indx] != 39
				&& e->v[e->i][e->indx] != 0)
				e->env[e->r][e->iter++] = e->v[e->i][e->indx++];
		}
	}
	e->env[e->r][e->iter] = '\0';
	e->env[++e->r] = NULL;
}

int	valid_element(t_env *e, int i, int j)
{
	int	j2;

	j2 = 0;
	if (e->v[i][0] == '=' || (e->v[i][j] >= '0' && e->v[i][j] <= '9'))
	{
		printf("bash: export: `%s': not a valid identifier\n", e->v[i]);
		e->exit_code = 1;
		return (1);
	}
	while (e->v[i][j2])
	{
		if (e->v[i][j2] == '-')
		{
			e->exit_code = 1;
			printf("bash: export: `%s': not a valid identifier\n", e->v[i]);
			return (1);
		}
		j2++;
	}
	return (0);
}

int	exporterror(t_env *e, int i, int j)
{
	while (e->v[i][j] != 0)
		j++;
	if (e->v[i][j - 1] != '=')
	{
		j = 0;
		while (e->v[i][j] != 0)
		{
			if (e->v[i][j] == '=')
			{
				while (e->v[i][j] != 0)
					j++;
				if (e->v[i][j - 1] == 34 || e->v[i][j - 1] == 39)
					return (1);
				else
					return (0);
			}
			j++;
		}
		return (1);
	}
	j = 0;
	return (exporapice(e, i, j));
}

void	espfun(t_env *e)
{
	if (e->v[e->i] == NULL)
		return ;
	if (e->v[e->i][0] == 'P' && e->v[e->i][1] == 'A' && e->v[e->i][2] == 'T'
		&& e->v[e->i][3] == 'H' && e->v[e->i][4] == '=')
		e->finded_path = 1;
	if (e->v[e->i][0] == ' ')
		return ;
	e->exit_code = 0;
	e->count_exp = -1;
	while (e->v[e->i] != NULL)
	{
		e->indx = 0;
		e->iter = 0;
		if (valid_element(e, e->i, 0) == 1 || exporterror(e, e->i, 0) == 1)
		{
			if (e->v[e->i + 1] != NULL && (e->v[e->i + 1][0] == 34 || \
			e->v[e->i + 1][0] == 39))
				e->i++;
			e->i++;
			e->exit = 1;
		}
		else
			cont_espfun(e);
	}
}
//export a=a b=' daw ad wd' c=c t="  da w dwd awd "  
//export a=a b=' daw ad wd' c=c t=
//export ciao="wad"
//export ciao='wad'
//export ciao= awawd