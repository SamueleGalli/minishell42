/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:43:52 by sgalli            #+#    #+#             */
/*   Updated: 2024/03/28 15:16:11 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	here_while(t_env *e, char *line, int i)
{
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGQUIT, handle_here);
		e->her = 1;
		line = readline("> ");
		if (check_here(e, line) == 2)
			printf("heredoc error \'%s\'\n", e->delim[i++]);
		else if (compare(line, e->delim[i]) == 1)
		{
			i++;
			if (final_here(e, i) == 1)
				break ;
		}
		else
			e->buffer = update_buffer_red(line, e->buffer, e);
		if (e->delim[i] == NULL)
		{
			break ;
		}
	}
	e->her = 0;
	e->i = e->i_here;
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
