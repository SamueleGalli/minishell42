/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:30:37 by sgalli            #+#    #+#             */
/*   Updated: 2022/10/19 14:38:28 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
	{
		return (0);
	}
	while ((i < n - 1) && s1[i] && s1[i] == s2[i])
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/*int	main(void)
{
	char str1[15] = "abcdef";
	char str2[15] = "ABCDEF";
	int result;

	result = ft_strncmp(str1, str2, 3);
	if(result < 0)
	{
		printf("str1 is less than str2\n");
	}else if(result >0){
		printf("str2 is less than str1\n");
	}
	else{
		printf("Value returned by strncmp() is: %d\n", result);
		return (0);
	}
}*/
