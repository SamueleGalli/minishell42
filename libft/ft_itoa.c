/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:16:47 by sgalli            #+#    #+#             */
/*   Updated: 2023/10/09 12:08:59 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	l(int n)
{
	int	ln;

	ln = 0;
	if (n == 0)
		return (1);
	if (n <= 0)
	{
		++ln;
	}
	while (n != 0)
	{
		++ln;
		n = n / 10;
	}
	return (ln);
}

char	*ft_itoa(int n)
{
	char	*r;
	int		ln;

	ln = l(n);
	r = malloc(ln + 1);
	if (r == NULL)
		return (NULL);
	r[ln] = '\0';
	if (n < 0)
	{
		r[0] = '-';
		n = -n;
	}
	else if (n == 0)
	{
		r[0] = '0';
	}
	while (n != 0)
	{
		--ln;
		r[ln] = n % 10 + '0';
		n = n / 10;
	}
	return (r);
}
