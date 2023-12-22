/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2023/08/03 09:59:49 by sgalli            #+#    #+#             */
/*   Updated: 2023/09/06 11:09:38 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	nuller(t_env *e)
{
	if (init_nuller(e) == 0)
		return ;
	while (e->v[e->i] != 0 && e->exit != 1)
	{
		if (compare(e->v[e->i], "echo") == 0 && \
		compare(e->v[e->i], "echo ") == 0)
			check_validation(e);
		if (e->is_valid == 1)
		{
			e->is_valid = 0;
			break ;
		}
		else
		{
			e->indx = 0;
			typing(e);
			update_i(e);
		}
	}
	e->stdin = dup(STDIN_FILENO);
	e->stdout = dup(STDOUT_FILENO);
	e->i = 0;
}

void	copy_env(t_env *e, char **env)
{
	int	i;

	i = 0;
	e->env = (char **)malloc(sizeof(char *) * size_mat(env));
	while (env[i] != NULL)
	{
		if (env[i][0] == 'P' && env[i][1] == 'A')
		{
			e->path = (char *)malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
			alloc_mat(e->path, env[i]);
		}
		e->env[i] = (char *)malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
		alloc_mat(e->env[i], env[i]);
		i++;
	}
	e->env[i] = NULL;
}

void	cont_allocation(t_env *e)
{
	e->start_red = 0;
	e->ex = 0;
	e->stdin = dup(STDIN_FILENO);
	e->stdout = dup(STDOUT_FILENO);
	e->mat_flag = NULL;
	e->exit_code = 0;
	e->p_i = 0;
	e->exit = 0;
	e->check = 0;
	e->sign = 0;
	e->input = 0;
	e->i_copy = 0;
	searchpath(e);
	e->space = 0;
	e->is_valid = 0;
	e->do_redir = 0;
	e->finded_path = 0;
	e->c_path = 0;
	e->red_flag = 0;
	e->check_input = -1;
}

void	alloc_e(int c, char **argv, char **env, t_env *e)
{
	e->p = NULL;
	e->cmd = NULL;
	e->v = NULL;
	e->s = NULL;
	copy_env(e, env);
	(void)c;
	(void)argv;
	e->i = 0;
	e->r = 0;
	e->valid = 0;
	e->status = 0;
	cont_allocation(e);
}

int	main(int c, char **argv, char **env)
{
	t_env	*e;

	e = malloc(sizeof(t_env));
	if (e == NULL)
		return (1);
	alloc_e(c, argv, env, e);
	while (1)
	{
		singals(e);
		free(e->cmd);
		e->cmd = readline("#> ");
		if (e->cmd == NULL)
			exiting_d(e);
		nuller(e);
		if (e->v != NULL)
			free_table(e->v);
		if (e->s != NULL)
			free(e->s);
		if (e->cmd[0] != '\0' && e->red_flag == 0)
			add_history(e->cmd);
		e->red_flag = 0;
	}
}
