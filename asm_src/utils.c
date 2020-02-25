/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stross <stross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 14:34:41 by stross            #+#    #+#             */
/*   Updated: 2020/02/25 15:24:05 by stross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	**split_aux(char **arr, char *str, char sep)
{
	int		i;

	i = 0;
	arr[i++] = str;
	while (*str)
	{
		if (*str == sep)
		{
			*str = '\0';
			str++;
			arr[i++] = str;
			continue ;
		}
		str++;
	}
	return (arr);
}

char		**split(char *str, char sep)
{
	char	**arr;
	int		lb_count;
	int		i;

	i = 0;
	lb_count = 1;
	while (str[i])
	{
		if (str[i] == sep)
			lb_count++;
		i++;
	}
	arr = (char**)ft_memalloc((lb_count + 2) * sizeof(char*));
	arr = split_aux(arr, str, '\n');
	return (arr);
}

void		remove_comments(char **arr)
{
	int		i;
	int		si;

	i = 0;
	while (arr[i])
	{
		si = 0;
		while (arr[i][si])
		{
			if (arr[i][si] == COMMENT_CHAR)
			{
				while (arr[i][si])
				{
					arr[i][si] = '\0';
					si++;
				}
				break ;
			}
			si++;
		}
		i++;
	}
}

int			ft_isspace(char ch)
{
	return (ch == ' ' || ch == '\t');
}

char		*ft_strcdup(char *str, char c)
{
	int		i;
	char	*ret;
	char	*mem;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	i++;
	ret = (char*)ft_memalloc(i--);
	mem = ret;
	while (i--)
		*ret++ = *str++;
	return (mem);
}
