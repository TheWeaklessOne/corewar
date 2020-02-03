/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoye <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 19:41:07 by djoye             #+#    #+#             */
/*   Updated: 2019/09/11 21:29:32 by djoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_s(char const *s, char c)
{
	int wc;

	wc = 0;
	while (*s != '\0')
	{
		if (*s != c)
		{
			while (*s != c && *s != '\0')
				s++;
			wc++;
			s--;
		}
		s++;
	}
	return (wc + 1);
}

static int	char_s(char const *s, char c, int i)
{
	int cc;

	cc = i;
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i - cc + 1);
}

static int	ft_free(char **str, int w)
{
	while (w >= 0)
	{
		free(str[w]);
		w--;
	}
	free(str);
	return (-1);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**str;
	int		w;
	int		i;
	int		j;

	if (!s || !(str = (char**)malloc(sizeof(char*) * word_s(s, c))))
		return (NULL);
	w = 0;
	i = -1;
	while (s[++i] != '\0')
	{
		if (s[i] != c)
		{
			if (!(str[w] = (char*)malloc(sizeof(char) * char_s(s, c, i))))
				if (ft_free(str, w) == -1)
					return (NULL);
			j = 0;
			while (s[i] != c && s[i] != '\0')
				str[w][j++] = s[i++];
			str[w++][j] = '\0';
			i--;
		}
	}
	str[w] = 0;
	return (str);
}
