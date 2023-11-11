/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:06:10 by sgalli            #+#    #+#             */
/*   Updated: 2023/11/10 11:04:03 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_flags(t_env *e)
{
	e->indx = e->i;
	e->count = 0;
	while (e->v[e->indx] != NULL)
	{
		if (e->v[e->indx][0] == '|' || e->v[e->indx][0] == '<'
			|| e->v[e->indx][0] == '>')
			break ;
		else if (strcom(e->v[e->indx], e->exit_code) == 0)
			e->indx++;
		else
		{
			e->count++;
			e->indx++;
		}
	}
}

int	check_value(t_env *e)
{
	char	*s;

	if (e->v[e->indx][0] == '$' && e->v[e->indx][1] == '?')
	{
		e->mat_flag[e->word] = (char *)malloc(sizeof(char ) * \
		l(e->exit_code) + 1);
		s = ft_itoa(e->exit_code);
		strcpy(e->mat_flag[e->word], s);
		e->word++;
		free(s);
		return (0);
	}
	return (1);
}

void	flag_continue(t_env *e)
{
	int	i;

	i = 0;
	e->iter = 0;
	while (e->v[e->indx][i] != '\0' && e->v[e->indx][i] != ' ')
	{
		if (e->v[e->indx][i] != 34 && e->v[e->indx][i] != 39
			&& e->v[e->indx][i] != '>' && e->v[e->indx][i] != '<')
			e->mat_flag[e->word][e->iter++] = e->v[e->indx][i++];
		else
			i++;
	}
	e->mat_flag[e->word][e->iter] = '\0';
}

void	split_flag(t_env *e)
{
	int	i;

	i = 0;
	e->iter = 0;
	e->iter = strcom(e->v[e->indx], e->exit_code);
	if (e->iter == 0)
		return ;
	if (e->v[e->indx + 1] == NULL)
		i++;
	if (check_value(e) == 0)
		return ;
	else
	{
		e->mat_flag[e->word] = (char *)malloc(sizeof(char) * e->iter + i + 1);
		flag_continue(e);
	}
	e->flag_i = 0;
}

void	flag_matrix(t_env *e)
{
	if (e->mat_flag != NULL)
		free_table(e->mat_flag);
	check_flags(e);
	e->mat_flag = (char **)malloc(sizeof(char *) * (e->count + 1));
	e->indx = e->i;
	e->numb = 0;
	e->iter = 0;
	e->word = 0;
	flag_while(e);
	e->mat_flag[e->word] = NULL;
}
