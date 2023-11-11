/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                    		                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 10:25:44 by sgalli            #+#    #+#             */
/*   Updated: 2023/09/07 12:37:32 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	str(t_env *e, int i, int j)
{
	int		k;

	k = 0;
	j--;
	e->p = (char *)malloc(sizeof(char) * 12);
	while (e->env[i][j] != ':')
	{
		e->p[k] = e->env[i][j];
		k++;
		j++;
	}
	e->p[k++] = '/';
	e->p[k] = 0;
}

int	path_find(char *str)
{
	if (ft_strncmp(str, "PATH", 4) != 0)
		return (1);
	return (0);
}

/*
** NOTE - possibile utilizzare ft_strcmp per vedere se le prime 4 lettere 
** sono PATH senza fare lettera per lettera il controllo (vedere funzione sopra)
** NOTE - cambiata ricerca del PATH con funzione dichiarata sopra, sembra
*/

void	searchpath(t_env *e)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (e->env[i] != NULL)
	{
		if (path_find(e->env[i]) == 0)
		{
			while (e->env[i][j] != '\0')
			{
				if (e->env[i][j] == 'u' && e->env[i][j + 4] == 'b')
				{
					str(e, i, j);
					return ;
				}
				j++;
			}
		}
		i++;
	}
}

/*
access X_OK da 0 se se il percorso assoluto esiste
se esiste lo alloco in p senno alloco singolarmente cartella e comando
assegno a v[o] il percorso corrente
lo eseguo usando execve
se da errore mette un errore comunemente usato per perror
se alloco dinamicamente con malloc la memoria a p la libero
*/
void	pathcmd(t_env *e)
{
	if (e->c_path == 1)
		return ;
	if (e->s != NULL)
		free(e->s);
	if (e->v[e->i][0] == 47)
	{
		e->s = malloc(ft_strlen(e->v[e->i]) + 1);
		ft_strcpy(e->s, e->v[e->i]);
		return ;
	}
	e->s = malloc(ft_strlen(e->p) + ft_strlen(e->v[e->i]) + 1);
	ft_strcpy(e->s, e->p);
	mini_strcat(e->s, e->v[e->i]);
}

void	check_path(t_env *e)
{
	int	i;

	i = 0;
	while (e->env[i] != NULL)
	{
		if (path_valid(e->env[i], e) == 1)
			return ;
		i++;
	}
	e->c_path = 1;
}
