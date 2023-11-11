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

/*
** TODO
	- Combinare pipe e redirections (NB: le redirections hanno priorita sui pipe)
** TODO - gestire comandi a cui rimangono aperti i figli (cat | cat | ls,
	dovrebbe stampre ls e chiudersi il comando dopo due enter)
*/
void	nuller(t_env *e)
{
	if (e->cmd[0] == '\0')
	{
		e->v = NULL;
		return ;
	}
	splitme(e);
	e->i = 0;
	e->exit = 0;
	while (e->v[e->i] != NULL && e->exit != 1)
	{
		if (invalid_cmd(e) == 1)
			break ;
		e->indx = 0;
		typing(e);
		update_i(e);
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
	e->init_red = 0;
	e->r = 0;
	e->status = 0;
	e->ex = 0;
	e->equal = 0;
	e->stdin = dup(STDIN_FILENO);
	e->stdout = dup(STDOUT_FILENO);
	e->mat_flag = NULL;
	e->exit_code = 0;
	e->p_i = 0;
	searchpath(e);
	e->space = 0;
	e->c_path = 0;
	e->red_flag = 0;
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
		if (e->v != NULL)
			free_table(e->v);
		e->cmd = readline("#> ");
		if (e->cmd == NULL)
			exiting_d(e);
		nuller(e);
		if (e->cmd[0] != '\0' && e->red_flag == 0)
			add_history(e->cmd);
		e->red_flag = 0;
	}
}
