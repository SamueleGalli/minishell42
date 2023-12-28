/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_help_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:20:33 by eraccane          #+#    #+#             */
/*   Updated: 2023/12/28 12:06:54 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	update_redir(t_env *e)
{
	update_in_out(e);
	if (e->v[e->i][0] == '<' && e->v[e->i][0] == '>' \
	&& (e->v[e->i] != NULL))
		e->i++;
	else
	{
		if (check_valid_red(e) == 0)
			return (0);
	}
	if (check_valid_red2(e) == 0)
		return (0);
	return (1);
}

char	*find_filepath(t_env *e)
{
	int	i;

	i = 0;
	while (e->v[i + 1] != NULL)
		i++;
	return (e->v[i]);
}

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

void	fork_cotinue(t_env *e, pid_t pid, int fd)
{
	if (pid == 0)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
		variabletype(e);
		exiting(e, 0);
	}
	else
		waitpid(pid, NULL, 0);
}

void	execve_red(t_env *e, int fd)
{
	close(0);
	dup2(fd, 1);
	close(fd);
	if (e->s != NULL)
	{
		if (e->c_path == 0 && access(e->s, X_OK) == 0 && check_builtin(e) == 0)
		{
			execve(e->s, e->mat_flag, e->env);
			perror("execve");
			exiting(e, 1);
		}
	}
	variabletype(e);
	exiting(e, 0);
}
