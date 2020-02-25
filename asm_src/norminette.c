/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norminette.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stross <stross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 12:45:08 by stross            #+#    #+#             */
/*   Updated: 2020/02/25 11:39:29 by stross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	norm_check_comm_bytes(int *i, int *x, int line, int row)
{
	*i = line;
	*x = row;
}

void	norm_set_struct(int *line, int *i)
{
	*line = 1;
	*i = 0;
}

void	norm_get_name_bytes(int *qm_count, int *i)
{
	*qm_count = 0;
	*i = 0;
}

void	norm_label(int *ti, char *str, int *si, bool *flag)
{
	while (LABEL_CHARS[*ti])
	{
		if (str[*si] == LABEL_CHARS[*ti])
			*flag = true;
		(*ti)++;
	}
}

void	norm_label2(char *str, int *i)
{
	while (str[*i])
	{
		if (str[*i] == LABEL_CHAR)
			break ;
		(*i)++;
	}
}
