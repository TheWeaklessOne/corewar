/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stross <stross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 14:27:08 by stross            #+#    #+#             */
/*   Updated: 2020/02/25 13:36:00 by stross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		c_add_sub(char *str, t_head *head, int mod, int *arr)
{
	char		*cpy;

	cpy = str + ft_strlen(g_op[mod - 1]);
	while (ft_isspace(*cpy))
		cpy++;
	if (check_instructions(cpy))
		invalid_ins_sim(arr, cpy, mod);
	if (*cpy != 'r')
		invalid_instruction(0, g_op[mod - 1]);
	find_separator(&cpy, mod, 1);
	if (*cpy != 'r')
		invalid_instruction(1, g_op[mod - 1]);
	find_separator(&cpy, mod, 2);
	if (*cpy != 'r')
		invalid_instruction(2, g_op[mod - 1]);
	check_after_arg(g_op[mod - 1], cpy);
	create_command(str, mod, 5, head);
}

void		c_ldi_lldi(char *str, t_head *head, int mod, int *arr)
{
	char		*cpy;
	int			temp;
	int			byte_size;

	cpy = str + ft_strlen(g_op[mod - 1]);
	while (ft_isspace(*cpy))
		cpy++;
	if (!(byte_size = 0) && check_instructions(cpy))
		invalid_ins_sim(arr, cpy, mod);
	if ((temp = instruction_size(*cpy, 2)))
		byte_size = temp;
	else
		invalid_instruction(0, g_op[mod - 1]);
	find_separator(&cpy, mod, 1);
	if ((temp = instruction_size(*cpy, 2)))
		byte_size += temp;
	else
		invalid_instruction(1, g_op[mod - 1]);
	find_separator(&cpy, mod, 2);
	if ((temp = instruction_size(*cpy, 2)))
		byte_size += temp + 2;
	else if (temp == 0 || temp == 1)
		invalid_instruction(2, g_op[mod - 1]);
	check_after_arg(g_op[mod - 1], cpy);
	create_command(str, mod, byte_size, head);
}

void		c_st(char *str, t_head *head, int mod, int *arr)
{
	char		*cpy;
	int			byte_size;

	cpy = str + ft_strlen(g_op[mod - 1]);
	while (ft_isspace(*cpy))
		cpy++;
	if (check_instructions(cpy))
		invalid_ins_sim(arr, cpy, mod);
	if (*cpy != 'r')
		invalid_instruction(0, g_op[mod - 1]);
	find_separator(&cpy, mod, 1);
	if (*cpy == DIRECT_CHAR)
		invalid_instruction(1, g_op[mod - 1]);
	byte_size = 3 + (*cpy == 'r' ? 1 : 2);
	check_after_arg(g_op[mod - 1], cpy);
	create_command(str, mod, byte_size, head);
}

void		c_sti(char *str, t_head *head, int mod, int *arr)
{
	char		*cpy;
	int			byte_size;
	int			temp;

	byte_size = 0;
	cpy = str + ft_strlen(g_op[mod - 1]);
	while (ft_isspace(*cpy))
		cpy++;
	if (check_instructions(cpy))
		invalid_ins_sim(arr, cpy, mod);
	if (*cpy != 'r')
		invalid_instruction(0, g_op[mod - 1]);
	find_separator(&cpy, mod, 1);
	if ((temp = instruction_size(*cpy, 2)))
		byte_size = temp + 3;
	find_separator(&cpy, mod, 2);
	if (*cpy != DIRECT_CHAR && *cpy != 'r')
		invalid_instruction(2, g_op[mod - 1]);
	if (*cpy == 'r')
		byte_size += 1;
	else
		byte_size += 2;
	check_after_arg(g_op[mod - 1], cpy);
	create_command(str, mod, byte_size, head);
}

void		c_aff(char *str, t_head *head, int mod, int *arr)
{
	char		*cpy;

	cpy = str + ft_strlen(g_op[mod - 1]);
	while (ft_isspace(*cpy))
		cpy++;
	if (check_instructions(cpy))
		invalid_ins_sim(arr, cpy, mod);
	if (*cpy != 'r')
		invalid_instruction(0, g_op[mod - 1]);
	check_after_arg(g_op[mod - 1], cpy);
	create_command(str, mod, 3, head);
}
