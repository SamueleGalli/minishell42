/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:43:55 by sgalli            #+#    #+#             */
/*   Updated: 2023/09/22 12:19:41 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

static int	ft_count(char const *s, char c)
{
	int	i;
	int	sn;

	i = 0;
	sn = 0;
	while (s[i] != 0)
	{
		if (s[i] != c)
		{
			sn++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		if (s[i] != '\0')
			i++;
	}
	return (sn);
}

static size_t	ft_superstrlen(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	**ft_split(const char *s, char c)
{
	int		i;
	int		ns;
	int		j;
	char	**str;

	j = 0;
	i = 0;
	ns = ft_count(s, c);
	str = (char **)malloc((ns + 1) * sizeof(char *));
	while (ns--)
	{
		while (s[i] != 0)
		{
			if (s[i] != c)
			{
				str[j] = ft_substr(s, i, ft_superstrlen(&s[i], c));
				i = i + ft_superstrlen(&s[i], c);
				break ;
			}
			i++;
		}
		j++;
	}
	str[j] = 0;
	return (str);
}
