/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_red_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:11:31 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/08 12:41:00 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	multiple_redirect(t_env *e)
{
	e->in_red = 0;
	e->out_red = 0;
	e->true_red = 0;
	while (e->v[e->i] != NULL && e->true_red == 0)
	{
		while (e->v[e->i][0] != '<' && e->v[e->i][0] != '>')
			e->i++;
		if ((e->v[e->i][1] != '>') && (search_mult_arrows(e, "< ") == 1 \
		|| search_mult_arrows(e, "> ") == 1 || search_mult_arrows(e, "<") == 1 \
		|| search_mult_arrows(e, ">") == 1))
			redirect_mult_single(e);
		else if (search_mult_arrows(e, ">> ") == 1 || \
	search_mult_arrows(e, ">>") == 1)
			redirect_mult_double(e);
		if (update_redir(e) == 0)
			break ;
	}
	if (e->in_red != 0 && e->out_red != 0)
		last_file(e);
	else if (e->in_red != 0 && e->true_red == 0)
		last_file_in(e);
	e->exit = 1;
}

void	single_major_mult_redirect(t_env *e)
{
	char	*filename;
	int		fd;

	filename = find_mult_filepath(e);
	if (e->v[e->i + 1] == NULL)
	{
		printf("error nothing after >\n");
		return ;
	}
	if (compare(e->v[e->i], ">") == 1 || compare(e->v[e->i], "> ") == 1)
	{
		fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0666);
		if (fd < 0)
		{
			e->exit = 1;
			printf("bash: %s: No such file or directory\n", filename);
			exiting(e, 0);
			close(fd);
		}
	}
	else
		check_red_fork(e, filename, 1);
}

void	redirect_mult_single(t_env *e)
{
	if (search_mult_arrows(e, "> ") == 1 || search_mult_arrows(e, ">") == 1)
		single_major_mult_redirect(e);
	else if (search_mult_arrows(e, "< ") == 1 \
	|| search_mult_arrows(e, "<") == 1)
		min_mult_redirect(e);
}

void	redirect_mult_double(t_env *e)
{
	char	*filename;
	int		fd;

	filename = find_mult_mult_filepath(e);
	if (compare(e->v[e->i], ">>") == 1 || compare(e->v[e->i], ">> ") == 1)
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

char	*find_lasth_filepath(t_env *e)
{
	int		i;
	char	*str;
	int		j;
	int		d;

	i = e->i;
	j = 0;
	d = ft_strlen_red(alloc_file(e, '>')) + 1;
	str = (char *)malloc(sizeof(char) * d);
	while (e->v[i] != NULL)
	{
		if (e->v[i][0] == '>')
		{
			i++;
			break ;
		}
		i++;
	}
	d = 0;
	while (e->v[i][j] != 0 && \
	e->v[i][j + 1] != ' ')
		str[d++] = e->v[i][j++];
	str[d] = '\0';
	return (str);
}
