/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoye <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 13:44:35 by djoye             #+#    #+#             */
/*   Updated: 2019/09/07 16:01:34 by djoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strnew(size_t size)
{
	size_t	i;
	char	*s;

	i = 0;
	s = (char*)malloc(sizeof(char) * (size + 1));
	if (s == NULL)
		return (NULL);
	while (i <= size)
	{
		s[i] = '\0';
		i++;
	}
	return (s);
}
