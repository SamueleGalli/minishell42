/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalli <sgalli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:55:17 by sgalli            #+#    #+#             */
/*   Updated: 2024/01/02 16:29:31 by sgalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_digit(char *s, t_env *e)
{
	int	i;

	i = 0;
	while (s[i] != 0)
	{
		if (s[i] == '-')
		{
			e->sign = -1;
			i++;
		}
		else if (s[i] == '+')
		{
			e->sign = 1;
			i++;
		}
		else if (s[i] == '\"')
			i++;
		else if ((s[i] >= '0' && s[i] <= '9') || s[i] == ' ')
			i++;
		else
			return (0);
	}
	return (1);
}

char	*mini_strcat(char *d, const char *s)
{
	int	i;
	int	k;

	k = 0;
	i = strcom(d, 0);
	while (s[k] != '\0' && s[k] != ' ')
	{
		if (s[k] == 34 || s[k] == 39 || s[k] == '<' || s[k] == '>')
			k++;
		else
			d[i++] = s[k++];
	}
	d[i] = '\0';
	return (d);
}

int	strcom(char *s, int e)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (s == NULL)
		return (0);
	if (s[0] != '\0' && s[1] != '\0')
	{
		if (s[0] == '$' && s[1] == '?')
			return (ft_strnum(e));
	}
	while (s[j] != 0)
	{
		if (s[j] == 34 || s[j] == 39)
			j++;
		else
		{
			i++;
			j++;
		}
	}
	return (i);
}
