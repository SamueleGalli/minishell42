/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cont_min_red_mult.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 09:29:46 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/05 13:01:23 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	min_child_parent(t_env *e, pid_t pid, int fd)
{
	if (pid == 0)
	{
		dup2(fd, STDIN_FILENO);
		e->i -= 1;
		if (check_builtin(e) == 0)
		{
			pathcmd(e);
			flag_matrix(e);
			if (e->c_path == 0 && access(e->s, X_OK) == 0
				&& check_builtin(e) == 0)
			{
				execve(e->s, e->mat_flag, e->env);
				perror("execve");
				exiting(e, 1);
			}
		}
		variabletype(e);
		exiting(e, 0);
	}
	else
		waitpid(pid, NULL, 0);
}

int	min_com(t_env *e)
{
	int	i;

	i = e->i;
	e->i--;
	while (e->i > 0 && e->v[e->i][0] != '|' && e->v[e->i][0] != '<'
		&& e->v[e->i][0] != '>')
		e->i--;
	if (e->i == 0 && e->v[e->i][0] != '>' && e->v[e->i][0] != '<')
	{
		e->i = i;
		return (1);
	}
	else if (e->v[e->i][0] == '|' || e->v[e->i][0] == '<'
		|| e->v[e->i][0] == '>')
	{
		e->i++;
		e->i = i;
		return (1);
	}
	return (0);
}
