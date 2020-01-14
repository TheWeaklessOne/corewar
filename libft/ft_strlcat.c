/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoye <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 11:51:37 by djoye             #+#    #+#             */
/*   Updated: 2019/09/09 19:52:35 by djoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t c;
	size_t sum;

	i = 0;
	c = 0;
	while (dst[i] != '\0')
		i++;
	while (src[c] != '\0')
		c++;
	if (size <= i)
		sum = size + c;
	else
		sum = c + i;
	c = 0;
	while (src[c] != '\0' && (i + c + 1) < size)
	{
		dst[i + c] = src[c];
		c++;
	}
	dst[i + c] = '\0';
	return (sum);
}
