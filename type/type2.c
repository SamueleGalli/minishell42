/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:44:45 by sgalli            #+#    #+#             */
/*   Updated: 2024/03/25 17:34:42 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dir_cont(t_env *e)
{
	char	cwd[1024];

	if (compare(e->v[e->i], "cd") == 1 && e->v[e->i + 1] == NULL)
	{
		go_root(e, 0);
		cont_pwd(e);
		return ;
	}
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
		if (e->v[e->i + 1][0] == '~')
			go_root(e, 0);
		else if (e->v[e->i + 2] != 0)
		{
			e->exit_code = 1;
			printf("bash: cd: too many arguments\n");
		}
		else if (e->v[e->i + 1][0] == '$')
			cd_dollar(e, 0, 0);
		else if (chdir(e->v[e->i + 1]) == -1)
		{
			e->exit = 1;
			e->exit_code = 1;
			printf("bash: cd: %s: No such file or directory\n", e->v[e->i + 1]);
			return ;
		}
		else
			e->exit_code = 0;
		cont_pwd(e);
		e->pwd = 1;
		return ;
	}
	dir_cont(e);
}

void	variabletype(t_env *e)
{
	if (e->v[e->i + 1] != NULL && next_valid(e->v[e->i + 1], e) == 1)
	{
		e->i++;
		espfun(e);
		check_path(e);
		return ;
	}
	else if (next_valid(e->v[e->i + 1], e) == 0)
		single_export(e);
	else if (compare(e->v[e->i], "unset") == 1)
	{
		if (e->v[e->i + 1] == NULL)
			return ;
		check_env(e);
		check_path(e);
		return ;
	}
	else if (compare(e->v[e->i], "env") == 1 && e->c_path == 0)
	{
		envionment(e);
		return ;
	}
	else
		writeme(e);
}
