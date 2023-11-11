/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contiue_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:43:59 by sgalli            #+#    #+#             */
/*   Updated: 2023/11/03 17:29:01 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	comparing(char *s, int i, char *s1, char *s2)
{
	int		j;
	int		k;

	j = i;
	k = 0;
	while (s[i] == s1[k] && s[i] != '\0' && s1[k] != '\0')
	{
		k++;
		i++;
	}
	if (s1[k] == '\0')
		return (1);
	k = 0;
	i = j;
	while (s[i] == s2[k] && s[i] != '\0' && s2[k] != '\0')
	{
		k++;
		i++;
	}
	if (s2[k] == '\0')
		return (1);
	return (0);
}

int	path_valid(char *s, t_env *e)
{
	if (s[0] == 'P' && s[1] == 'A' && s[2] == 'T' \
	&& s[3] == 'H' && s[4] == '=' && s[5] != '\0')
	{
		if (comparing(s, 5, "/usr/bin/", "/bin/") == 1)
		{
			e->c_path = 0;
			return (1);
		}
	}
	return (0);
}
