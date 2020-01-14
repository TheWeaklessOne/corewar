/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoye <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 22:16:50 by djoye             #+#    #+#             */
/*   Updated: 2019/09/11 12:22:39 by djoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*dest;
	char	*source;

	i = 0;
	dest = (char*)dst;
	source = (char*)src;
	if (len == 0 || dst == source)
		return (dst);
	if (dest > source)
		while (++i <= len)
			dest[len - i] = source[len - i];
	else
	{
		while (len > 0)
		{
			*dest = *source;
			dest++;
			source++;
			len--;
		}
	}
	return (dst);
}
