/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 12:07:08 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/02 15:55:56 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_str(char *s, int i)
{
	if (s == NULL)
		return ;
	while (s[i] != '\0')
		printf("%c", s[i++]);
}

int	control_match(char *s)
{
	int		i;
	char	c;

	i = 0;
	c = s[0];
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	check_closure(char *s)
{
	int	i;

	i = 1;
	if (control_match(s) == 1)
		return (0);
	while (s[i] != '\0' && s[i] != 34 && s[i] != 39)
		i++;
	if (s[i] == '\0')
		return (1);
	else if (s[i] != s[0])
		return (1);
	return (0);
}
