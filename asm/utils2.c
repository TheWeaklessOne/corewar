/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stross <stross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 15:05:38 by stross            #+#    #+#             */
/*   Updated: 2020/02/07 15:14:00 by stross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	ft_strchlen(char *str, char ch)
{
	int i;

	i = 0;
	while (str[i] && str[i] != ch)
		i++;
	return (i);
}

int	strstr_zero(char *hey, char *need)
{
	while (*hey && *need)
	{
		if (*hey == *need)
		{
			hey++;
			need++;
			if (*need == '\0')
				return (1);
		}
		else
			return (0);
	}
	return (0);
}