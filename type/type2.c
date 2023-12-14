/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:44:45 by sgalli            #+#    #+#             */
/*   Updated: 2023/12/13 12:52:53 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dir_cont(t_env *e)
{
	char	cwd[1024];

	if (compare(e->v[e->i], "pwd") == 1)
	{
		if (getcwd(cwd, 1024) != NULL)
			printf("%s\n", cwd);
		else
		{
			e->exit = 1;
			perror("pwdr");
		}
		return ;
	}
	else
		com(e);
}

void	directory(t_env *e)
{
	if (compare(e->v[e->i], "cd") == 1 && e->v[e->i + 1] != NULL)
	{
		if (e->v[e->i + 1][0] == '$')
			cd_dollar(e, 0, 0);
		else if (chdir(e->v[e->i + 1]) == -1 && e->v[e->i + 2] == 0)
		{
			e->exit = 1;
			e->exit_code = 1;
			perror("cd");
		}
		else
			printf("bash: cd: too many arguments1\n");
		return ;
	}
	else if (compare(e->v[e->i], "cd") == 1)
		return ;
	dir_cont(e);
}

void	variabletype(t_env *e)
{
	if (compare(e->v[e->i], "export") == 1 && e->v[e->i + 1] != NULL)
	{
		e->i++;
		espfun(e);
		check_path(e);
		return ;
	}
	else if (compare(e->v[e->i], "unset") == 1)
	{
		if (e->v[e->i + 1] == NULL)
			return ;
		check_env(e);
		check_path(e);
		return ;
	}
	else if (compare(e->v[e->i], "env") == 1)
	{
		envionment(e);
		return ;
	}
	else
		writeme(e);
}
