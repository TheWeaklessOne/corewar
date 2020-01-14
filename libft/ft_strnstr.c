/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoye <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 12:23:59 by djoye             #+#    #+#             */
/*   Updated: 2019/09/12 11:37:39 by djoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	f;
	size_t	c;
	char	*str;

	i = 0;
	str = (char*)haystack;
	while (haystack[i] != '\0')
	{
		c = i;
		f = 0;
		while (haystack[i] == needle[f] && i < len && needle[f] != '\0')
		{
			i++;
			f++;
		}
		if (needle[f] == '\0')
			return (str + c);
		else
			i = i - f;
		i++;
	}
	return (0);
}
