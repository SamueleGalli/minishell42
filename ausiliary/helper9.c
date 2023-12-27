/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper9.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 11:40:57 by sgalli            #+#    #+#             */
/*   Updated: 2023/12/27 11:43:12 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_tilde(char *s, int i)
{
	while (s[i] != 0)
		i++;
	return (i);
}

void	tilde_or_not(t_env *e, char *tmp)
{
	if (tmp[0] == '~')
	{
		go_root(e, 0);
		return ;
	}
	else if (chdir(tmp) == -1)
	{
		e->exit_code = 1;
		e->exit = 1;
		printf("bash: cd: %s: No such file or directory\n", tmp);
	}
}
