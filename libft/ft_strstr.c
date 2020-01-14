/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoye <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 11:02:51 by djoye             #+#    #+#             */
/*   Updated: 2019/09/12 11:25:21 by djoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	int		f;
	int		c;
	char	*str;

	i = 0;
	f = 0;
	str = (char*)haystack;
	if (needle[f] == '\0')
		return (str);
	while (haystack[i] != '\0')
	{
		c = i;
		while (haystack[i] == needle[f] && haystack[i] != '\0')
		{
			f++;
			i++;
		}
		if (needle[f] == '\0')
			return (str + c);
		i = i - f;
		f = 0;
		i++;
	}
	return (NULL);
}
