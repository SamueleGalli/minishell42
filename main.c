/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 09:56:59 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/05 09:56:59 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_nuller(t_env *e)
{
	e->pi_re = 0;
	e->output = 0;
	e->input = 0;
	e->s = NULL;
	if (e->cmd[0] == '\0')
	{
		e->v = NULL;
		return (0);
	}
	splitme(e);
	e->i = 0;
	e->exit = 0;
	return (1);
}

void	nuller(t_env *e)
{
	if (init_nuller(e) == 0)
		return ;
	while (e->v[e->i] != 0 && e->exit != 1)
	{
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

void	cont_allocation(t_env *e)
{
	e->start_red = 0;
	e->ex = 0;
	e->stdin = dup(STDIN_FILENO);
	e->stdout = dup(STDOUT_FILENO);
	e->mat_flag = NULL;
	e->exit_code = 0;
	e->exit = 0;
	e->check = 0;
	e->i_tmp = 0;
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
	e->out_red = 0;
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
