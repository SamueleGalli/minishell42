/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 09:27:45 by marvin            #+#    #+#             */
/*   Updated: 2024/03/22 12:31:40 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	arrows_number(t_env *e)
{
	int	i;
	int	red_num;

	i = 0;
	red_num = 0;
	while (e->v[i] != NULL)
	{
		if (e->v[i][0] == '<' || e->v[i][0] == '>' || e->v[i][1] == '>'
			|| e->v[i][1] == '<')
			red_num++;
		i++;
	}
	return (red_num);
}

void	type_cont(t_env *e)
{
	if (compare(e->v[e->i], "exit") == 1 && e->exit != 1)
		what_exit(e);
	else if (e->v != NULL && e->exit != 1)
		variabletype(e);
}

void	typing(t_env *e)
{
	char p[1024];

	if (getcwd(p, 1024) != NULL)
	{
		if (e->tmp_pwd != 0)
			free(e->tmp_pwd);
		e->tmp_pwd = (char *)malloc(sizeof(char ) * (ft_strlen(p) + 1));
	}
	alloc_mat(e->tmp_pwd, p);
	if (is_pipe_red(e) == 1)
		pipe_and_redirection(e);
	else
		type_cont(e);
	return ;
}
