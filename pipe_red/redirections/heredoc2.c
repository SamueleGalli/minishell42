/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:41:45 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/23 12:30:51 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	continuing_minor_double(t_env *e, char *s, pid_t pid)
{
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
		continue_heredoc(e, s);
	else
		waitpid(pid, NULL, 0);
	free(s);
}

void	redirect_double_arrows(t_env *e, char *buffer)
{
	pid_t	pid;
	char	*s;

	s = alloc_s(buffer);
	free(buffer);
	pid = fork();
	continuing_minor_double(e, s, pid);
}

int	num_here(t_env *e)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (e->v[i] != NULL && e->v[i][0] != '|' && e->v[i][0] != '>' && \
	!(e->v[i][0] == '<' && e->v[i][1] == 0))
	{
		if ((compare(e->v[i], "<<") == 1 || compare(e->v[i], "<< ") == 1) \
		&& e->v[i + 1] != NULL)
		{
			if (e->v[e->i + 2] != NULL)
				e->here = i + 2;
			else
				e->here = i + 1;
			j++;
		}
		i++;
	}
	return (j);
}

void	alloc_delim(t_env *e, int i, int j)
{
	int	k;

	k = 0;
	e->delim[j] = (char *)malloc(sizeof(char) * \
	(ft_strlen(e->v[i + 1]) + 1));
	i++;
	while (e->v[i][k] != '\0' && e->v[i][k] != ' ')
	{
		e->delim[j][k] = e->v[i][k];
		k++;
	}
	e->delim[j][k] = '\0';
}

void	alloc_all_here(t_env *e)
{
	int	i;
	int	j;

	j = 0;
	i = num_here(e);
	e->delim = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (e->v[i] != NULL && e->v[i][0] != '|' && e->v[i][0] != '>' && \
	!(e->v[i][0] == '<' && e->v[i][1] == 0))
	{
		if ((compare(e->v[i], "<<") == 1 || compare(e->v[i], "<< ") == 1) \
		&& e->v[i + 1] != NULL)
		{
			alloc_delim(e, i, j);
			j++;
		}
		i++;
	}
	e->delim[j] = NULL;
}
