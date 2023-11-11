/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:40:20 by sgalli            #+#    #+#             */
/*   Updated: 2022/10/25 15:39:23 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	i++;
	while (--i)
	{
		if (s[i] == (unsigned char)c)
		{
			return ((char *)(s + i));
		}
	}
	if (s[0] == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}
