/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   major_red.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 13:07:09 by eraccane          #+#    #+#             */
/*   Updated: 2024/01/03 11:38:10 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	double_major_redirect(t_env *e)
{
	char	*filename;
	int		fd;

	filename = find_filepath(e);
	if (compare(e->v[0], ">>") == 1 || compare(e->v[0], ">> ") == 1)
	{
		fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0666);
		if (fd < 0)
		{
			e->exit_code = 1;
			printf("bash: %s: No such file or directory\n", filename);
			exiting(e, 0);
		}
		close(fd);
	}
	else
		check_red_fork(e, filename, 2);
}

char	*alloc_s(char *buf)
{
	int		i;
	char	*t;

	t = (char *)malloc(sizeof(char ) * ft_strlen(buf) + 1);
	i = 0;
	while (buf[i] != 0)
	{
		t[i] = buf[i];
		i++;
	}
	t[i] = 0;
	return (t);
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
