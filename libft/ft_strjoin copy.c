/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 12:15:40 by sgalli            #+#    #+#             */
/*   Updated: 2023/10/12 16:08:26 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strjoin(char *s1, char *s2)
{
	char	*st;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1)
		return (s2);
	else if (!s2)
		return (s1);
	else if (!s1 && !s2)
		return (NULL);
	st = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (st == NULL)
		return (NULL);
	while (s1[i])
	{
		st[i] = s1[i];
		i++;
	}
	while (s2[j])
		st[i++] = s2[j++];
	st[i] = 0;
	return (st);
}

void	continue_join_n(char *st, char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		st[i] = s1[i];
		i++;
	}
	st[i] = '\n';
	while (s2[j])
		st[i++] = s2[j++];
	st[i] = '\n';
	i++;
	st[i] = 0;
}

char	*ft_strjoin_n(char *s1, char *s2)
{
	char	*st;

	if (!s1)
	{
		st = (char *)malloc(sizeof(char) * (ft_strlen(s2) + 1 + 1));
		st = ft_strcpy(st, s2);
		st[ft_strlen(st)] = '\n';
		st[ft_strlen(st) + 1] = '\0';
		return (st);
	}
	else if (!s2)
	{
		st = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
		st = ft_strcpy(st, s1);
		st[ft_strlen(st)] = '\n';
		st[ft_strlen(st) + 1] = '\0';
		return (st);
	}
	else if (!s1 && !s2)
		return (NULL);
	st = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1 + 2));
	if (st == NULL)
		return (NULL);
	continue_join_n(st, s1, s2);
	return (st);
}
