/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoye <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 16:32:41 by djoye             #+#    #+#             */
/*   Updated: 2019/09/09 20:46:40 by djoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*arr;
	int		i;

	i = 0;
	arr = (char*)s;
	while (arr[i] != '\0')
		i++;
	while (i >= 0)
	{
		if (arr[i] == c)
			return (arr + i);
		i--;
	}
	return (NULL);
}
