/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper12.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 11:28:01 by sgalli            #+#    #+#             */
/*   Updated: 2023/12/27 11:45:09 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_max_min(t_env *e)
{
	if (e->v[e->i + 1] != NULL)
	{
		if (ft_strlen(e->v[e->i + 1]) == 19 && e->v[e->i + 1][18] >= '8')
		{
			printf("bash: exit: %s: numeric argument required\n", e->v[e->i
				+ 1]);
			exiting(e, 2);
		}
		else if (ft_strlen(e->v[e->i + 1]) == 20 && e->v[e->i + 1][19] > '8')
		{
			printf("bash: exit: %s: numeric argument required\n", e->v[e->i
				+ 1]);
			exiting(e, 2);
		}
	}
}

void	check_red_other(t_env *e)
{
	if (e->cmd[e->indx] == '|' || e->cmd[e->indx] == '<'
		|| e->cmd[e->indx] == '>')
	{
		while ((e->cmd[e->indx] == '|' || e->cmd[e->indx] == '<'
				|| e->cmd[e->indx] == '>'))
			e->indx++;
		e->word++;
	}
}

void	splong_red(t_env *e)
{
	while (e->cmd[e->j] == '|' || e->cmd[e->j] == '<' || e->cmd[e->j] == '>')
	{
		e->j++;
		e->word++;
	}
}

void	write_redir(t_env *e)
{
	while (e->cmd[e->indx] == '|' || e->cmd[e->indx] == '<'
		|| e->cmd[e->indx] == '>')
		e->v[e->i][e->lenght++] = e->cmd[e->indx++];
}

int	is_pipredir(char *s)
{
	if (s[0] == '|' || s[0] == '<' || s[0] == '>')
		return (1);
	return (0);
}
