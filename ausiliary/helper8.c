/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper8.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 09:51:17 by sgalli            #+#    #+#             */
/*   Updated: 2023/12/20 12:09:38 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_env(t_env *e, int i)
{
	int	j;
	int	k;

	k = 0;
	j = e->expand;
	while (e->env[i][j] != 0)
	{
		if (e->env[i][j] == ' ')
			j++;
		else
		{
			k++;
			j++;
		}
	}
	return (k);
}

void	expand(t_env *e, int i)
{
	char	*tmp;
	int		l;

	l = 0;
	l = len_env(e, i);
	tmp = (char *)malloc(sizeof(char) * (l + 1));
	l = 0;
	while (e->env[i][e->expand] != 0)
	{
		if (e->env[i][e->expand] == ' ')
			e->expand++;
		else
			tmp[l++] = e->env[i][e->expand++];
	}
	tmp[l] = 0;
	tilde_or_not(e, tmp);
	free(tmp);
}

void	go_tilde(t_env *e, int i, int j)
{
	char	*tmp;
	int		i2;

	i2 = 0;
	tmp = malloc(sizeof(char) * (len_tilde(e->env[i], j) + 1));
	while (e->env[i][j] != '\0')
		tmp[i2++] = e->env[i][j++];
	tmp[i2] = '\0';
	if (chdir(tmp) == -1)
	{
		e->exit = 1;
		e->exit_code = 1;
		printf("bash: cd: %s: No such file or directory\n", tmp);
	}
	free(tmp);
}

void	go_root(t_env *e, int i)
{
	while (e->env[i] != NULL)
	{
		if (e->env[i][0] == 'H' && e->env[i][1] == 'O' && e->env[i][2] == 'M' \
		&& e->env[i][3] == 'E')
		{
			go_tilde(e, i, 5);
			return ;
		}
		i++;
	}
}

void	var_quote(t_env *e, int j, int iter, int i)
{
	e->word = 1;
	while (e->env[++iter] != NULL)
	{
		while (e->v[j][e->word + 1] == e->env[iter][i])
		{
			i++;
			e->word++;
		}
		if (e->env[iter][i] == '=' && (e->v[j][e->word + 1] == ' ' \
		|| e->v[j][e->word + 1] == 34 || e->v[j][e->word + 1] == '$' \
		|| e->v[j][e->word + 1] == 0))
		{
			printf_env(e, iter);
			if (e->v[j + 1] != NULL)
				printf(" ");
			return ;
		}
		else
		{
			e->word = 1;
			i = 0;
		}
	}
}
