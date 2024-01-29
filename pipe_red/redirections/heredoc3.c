/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:43:52 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/29 09:52:41 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	here_while(t_env *e, char *line, char *buffer, int i)
{
	while (1)
	{
		line = readline("> ");
		singals(e);
		if (check_signals_red(e, line) == 1)
			break ;
		if (compare(line, e->delim[i]) == 1)
		{
			i++;
			if (e->delim[i] == NULL)
			{
				redirect_double_arrows(e, buffer);
				break ;
			}
			else
			{
				free(buffer);
				buffer = NULL;
			}
		}
		else
			buffer = update_buffer_red(line, buffer, e);
	}
	e->i = e->i_here;
}

void	shoreter_else(t_env *e, char *s)
{
	if (e->here_pipe == 1)
	{
		close(e->pipefd[0]);
		dup2(e->pipefd[1], STDOUT_FILENO);
		close(e->pipefd[1]);
	}
	if (compare(e->v[e->i], "cat") == 1)
	{
		if (s == 0)
			e->no_here = 1;
		else
			printf("%s", s);
	}
	else
		variabletype(e);
}

char	*converting(t_env *e, int j, int k, char *line)
{
	int	i;
	int	i2;

	i2 = 0;
	i = k;
	while (e->env[j][i] != 0)
	{
		i2++;
		i++;
	}
	free(line);
	line = (char *)malloc(sizeof(char) * (i2 + 1));
	i2 = 0;
	while (e->env[j][k] != 0)
	{
		line[i2] = e->env[j][k];
		i2++;
		k++;
	}
	line[i2] = '\0';
	return (line);
}

char	*last_here(char *line)
{
	char	*l;

	free(line);
	l = (char *)malloc(sizeof(char) * 1);
	l[0] = '\0';
	return (l);
}

char	*convert_line(char *line, t_env *e, int j, int k)
{
	int	i;

	i = 1;
	while (e->env[j] != NULL)
	{
		while (e->env[j][k] == line[i])
		{
			k++;
			i++;
		}
		if (e->env[j][k] == '=')
			return (converting(e, j, ++k, line));
		else
		{
			i = 1;
			k = 0;
			j++;
		}
	}
	return (last_here(line));
}
