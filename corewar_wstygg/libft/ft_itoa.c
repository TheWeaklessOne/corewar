/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoye <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 14:46:22 by djoye             #+#    #+#             */
/*   Updated: 2019/09/10 16:23:05 by djoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	*s;
	long	nb;
	int		i;

	i = 0;
	nb = n;
	if (n <= 0)
		i++;
	while (n && i++ >= 0)
		n = n / 10;
	if ((s = (char*)malloc(sizeof(char) * (i + 1))) == NULL)
		return (NULL);
	if (nb < 0)
		s[0] = '-';
	if (nb == 0)
		s[0] = '0';
	s[i--] = '\0';
	nb = nb < 0 ? -nb : nb;
	while (nb)
	{
		s[i--] = nb % 10 + '0';
		nb = nb / 10;
	}
	return (s);
}
