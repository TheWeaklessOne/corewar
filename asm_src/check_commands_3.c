/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stross <stross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 14:28:33 by stross            #+#    #+#             */
/*   Updated: 2020/02/25 12:53:05 by stross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		check_after_arg(char *inst, char *str)
{
	while (*str == LABEL_CHAR || *str == 'r' || *str == '%'
	|| (*str >= '0' && *str <= '9') || *str == '-')
	{
		if (*str == LABEL_CHAR)
		{
			while (*str && *str != ' ' &&
			*str != '\t' && *str != SEPARATOR_CHAR)
				str++;
		}
		if (*str)
			str++;
	}
	while (ft_isspace(*str))
		str++;
	if (*str)
	{
		write(2, "Invalid arguments fot instruction ", 34);
		ft_putstr_fd(inst, 2);
		write(2, "\n", 1);
		exit(1);
	}
}

void		find_separator(char **cpy, int mod, int num)
{
	while (**cpy != SEPARATOR_CHAR && **cpy)
		(*cpy)++;
	if (!**cpy)
		invalid_instruction(num, g_op[mod - 1]);
	(*cpy)++;
	while (ft_isspace(**cpy))
		(*cpy)++;
}

static void	c_and_xor_or_help(int *temp, int *byte_size, char cpy, int mod)
{
	if ((*temp = instruction_size(cpy, 4)))
	{
		if (*temp != 1)
			invalid_instruction(2, g_op[mod - 1]);
		*byte_size += *temp + 2;
	}
	else
		invalid_instruction(2, g_op[mod - 1]);
}

void		c_and_xor_or(char *str, t_head *head, int mod, int *arr)
{
	char		*cpy;
	int			temp;
	int			byte_size;

	byte_size = 0;
	cpy = str + ft_strlen(g_op[mod - 1]);
	while (ft_isspace(*cpy))
		cpy++;
	if (check_instructions(cpy))
		invalid_ins_sim(arr, cpy, mod);
	if ((temp = instruction_size(*cpy, 4)))
		byte_size = temp;
	else
		invalid_instruction(0, g_op[mod - 1]);
	find_separator(&cpy, mod, 1);
	if ((temp = instruction_size(*cpy, 4)))
		byte_size += temp;
	else
		invalid_instruction(1, g_op[mod - 1]);
	find_separator(&cpy, mod, 2);
	c_and_xor_or_help(&temp, &byte_size, *cpy, mod);
	check_after_arg(g_op[mod - 1], cpy);
	create_command(str, mod, byte_size, head);
}
