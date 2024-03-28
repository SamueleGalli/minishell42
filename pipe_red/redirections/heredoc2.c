/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:41:45 by sgalli            #+#    #+#             */
/*   Updated: 2024/03/28 13:26:59 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//wc << here
//cat << here > file1

void	continuing_minor_double(t_env *e, pid_t pid)
{
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
		continue_heredoc(e);
	else
	{
		waitpid(pid, &e->status, 0);
		if (e->here_pipe == 1)
		{
			close(e->pipefd[1]);
			dup2(e->pipefd[0], STDIN_FILENO);
			close(e->pipefd[0]);
		}
	}
	if (e->here_p != 0)
		free(e->here_p);
}

void	redirect_double_arrows(t_env *e, char *buffer)
{
	pid_t	pid;

	e->exit_code = 0;
	e->here_p = alloc_s(buffer);
	if (buffer != 0)
		free(buffer);
	pid = fork();
	continuing_minor_double(e, pid);
}

int	num_here(t_env *e)
{
	int	i;
	int	j;

	i = e->i;
	j = 0;
	while (e->v[i] != NULL && e->v[i][0] != '|' && e->v[i][0] != '>')
	{
		if ((compare(e->v[i], "<<") == 1 || compare(e->v[i], "<< ") == 1) \
		&& e->v[i + 1] != NULL)
		{
			e->i_here = i + 2;
			e->here = 1;
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
	i = e->i;
	while (e->v[i] != NULL && e->v[i][0] != '|' && e->v[i][0] != '>')
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
