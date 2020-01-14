/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoye <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 17:26:21 by djoye             #+#    #+#             */
/*   Updated: 2019/09/11 17:42:30 by djoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char			*str;
	unsigned int	i;
	unsigned int	f;
	unsigned int	l;

	f = 0;
	if (s == NULL)
		return (NULL);
	while (s[f] == ' ' || s[f] == '\t' || s[f] == '\n')
		f++;
	i = 0;
	while (s[i] != '\0')
		i++;
	while (i && (s[i - 1] == ' ' || s[i - 1] == '\t' || s[i - 1] == '\n'))
		i--;
	l = i;
	if ((str = (char*)malloc(sizeof(char) * (l - f + 1))) == NULL)
		return (NULL);
	i = 0;
	while (f < l)
		str[i++] = s[f++];
	str[i] = '\0';
	return (str);
}
