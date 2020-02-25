/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norminette2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stross <stross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 13:38:42 by stross            #+#    #+#             */
/*   Updated: 2020/02/25 11:39:29 by stross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	norm_check_string(t_head *head, int line, int row, char *str)
{
	if (head->name_ex)
		unexpected_token(line, row, str);
	else
		get_name_bytes(str, head, line, row);
}

void	norm_get_label(t_label *l, int *mod, t_command **commands)
{
	while (l->comm < l->lab)
	{
		l->dist += commands[l->comm]->byte_size;
		l->comm++;
	}
	*mod = 1;
}

void	norm_get_label2(t_label *l, int *mod, t_command **commands)
{
	while (l->comm > l->lab)
	{
		l->dist += commands[l->lab]->byte_size;
		l->lab++;
	}
	*mod = 2;
}

void	norm_get_ext(int *mod, char **f_name, int i, char **filename)
{
	*mod = DISASM;
	if (!(*f_name = (char*)ft_memalloc(i + 3)))
		error_allocation();
	ft_strncpy(*f_name, *filename, ++i);
	ft_strncpy(*f_name + i, "s", 1);
}

void	check_end_token(int line, int row, char *str, int mod)
{
	char	*cpy;

	cpy = str;
	if (mod == 1)
	{
		str += ft_strlen(NAME_CMD_STRING);
		while (*str && *str != '"')
		{
			if (*str != ' ' && *str != '\t')
				unexpected_token(line, row, cpy);
			str++;
		}
	}
	else
	{
		str += ft_strlen(COMMENT_CMD_STRING);
		while (*str && *str != '"')
		{
			if (*str != ' ' && *str != '\t')
				unexpected_token(line, row, cpy);
			str++;
		}
	}
}
