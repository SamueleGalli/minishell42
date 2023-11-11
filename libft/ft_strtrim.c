/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:08:28 by sgalli            #+#    #+#             */
/*   Updated: 2023/11/07 17:29:01 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_controllaset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		j;
	int		i;
	int		l;
	char	*s2;

	j = 0;
	i = 0;
	l = ft_strrlen(s1);
	if (s1 == 0 || set == 0)
		return (0);
	while (s1[i] && ft_controllaset(s1[i], set) != 0)
		i++;
	while (l > i && ft_controllaset(s1[l - 1], set))
		l--;
	s2 = (char *)malloc(sizeof(char) * l - i + 1);
	if (!s2)
		return (NULL);
	while (i < l)
	{
		s2[j] = s1[i];
		j++;
		i++;
	}
	s2[j] = '\0';
	return (s2);
}
