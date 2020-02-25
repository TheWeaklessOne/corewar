/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stross <stross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 15:05:38 by stross            #+#    #+#             */
/*   Updated: 2020/02/25 11:39:29 by stross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_strchlen(char *str, char ch)
{
	int i;

	i = 0;
	while (str[i] && str[i] != ch)
		i++;
	return (i);
}

int		strstr_zero(char *hey, char *need)
{
	while (*hey && *need)
	{
		if (*hey == *need)
		{
			hey++;
			need++;
			if (*need == '\0')
				return (1);
		}
		else
			return (0);
	}
	return (0);
}

void	get_name_bytes(char *str, t_head *head, int line, int row)
{
	int		qm_count;
	int		i;

	head->name_ex = true;
	norm_get_name_bytes(&qm_count, &i);
	while (str[i])
	{
		if (str[i] == '"')
			qm_count++;
		i++;
	}
	if (qm_count != 2)
		name_syntax(str, line, row, 1);
	else
	{
		i = 0;
		str = ft_strchr(str, '"');
		str++;
		while (*str && *str != '"')
		{
			if (i > PROG_NAME_LENGTH)
				length_error(1);
			head->name[i++] = *str++;
		}
	}
}
