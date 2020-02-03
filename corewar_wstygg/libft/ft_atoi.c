/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoye <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 18:49:24 by djoye             #+#    #+#             */
/*   Updated: 2019/09/10 20:39:29 by djoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	unsigned long long	nb;
	int					sgn;

	nb = 0;
	sgn = 1;
	while (*str == '\n' || *str == '\t' || *str == '\v'
			|| *str == '\r' || *str == '\f' || *str == ' ')
		str++;
	if (*str == '-')
		sgn = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		nb = nb * 10 + (*str - '0');
		str++;
	}
	if (sgn == 1 && nb >= 9223372036854775807)
		return (-1);
	else if (sgn == -1 && nb > 9223372036854775807)
		return (0);
	return (nb * sgn);
}
