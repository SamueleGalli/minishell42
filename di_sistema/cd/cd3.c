/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd3.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:46:12 by sgalli            #+#    #+#             */
/*   Updated: 2024/03/21 14:59:09 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**copy_pwd(t_env *e, char **tmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (e->env[i] != NULL)
	{
		tmp[j] = (char *)malloc(sizeof(char) * (ft_strlen(e->env[i]) + 1));
		alloc_mat(tmp[j], e->env[i]);
		printf("tmp[j] = %s\n", tmp[j]);
		j++;
		i++;
	}
	tmp[j] = NULL;
	return (tmp);
}

void	cont_pwd(t_env *e, int i, char *p)
{
	char	**tmp;

	i = i;
	p = p;
	tmp = (char **)malloc(sizeof(char *) * (size_mat(e->env) + 1));
	tmp = copy_pwd(e, tmp);
	//free_table(e->env);
	//e->env = (char **)malloc(sizeof(char *) * (size_mat(tmp)));
	free(p);
	free(tmp);
}
