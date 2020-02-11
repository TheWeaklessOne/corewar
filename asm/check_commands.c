/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stross <stross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 15:38:18 by stross            #+#    #+#             */
/*   Updated: 2020/02/10 15:43:25 by stross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	instruction_size(char ch, int size)
{
	if (ch == 'r')
		return (1);
	else if (ch == ' ' || (ch >= '0' && ch <= '9') || ch == LABEL_CHAR)
		return (2);
	else if (ch == '%')
		return (size);
	else
		return (0);
}

int	check_instructions(char *str)
{
	int		i;

	i = 0;
	while (*str)
	{
		if (*str == LABEL_CHAR)
		{
			while (*str && *str != ' ' && *str != SEPARATOR_CHAR && *str != DIRECT_CHAR)
			{
				i++;
				str++;
			}
			if (!*str)
				return (0);
		}
		if (*str != SEPARATOR_CHAR && *str != DIRECT_CHAR &&
		*str != ' ' && *str != '\t' && *str != LABEL_CHAR &&
		!(*str >= '0' && *str <= '9') && *str && *str != '-' && *str != 'r')
			return (i);
		str++;
		i++;
	}
	return (0);
}

void		c_live_zjmp_fork_lfork(char *str, t_head *head, int mod, int *arr)
{
	t_command	*command;
	char		*cpy;

	cpy = str + ft_strlen(g_op[mod - 1]);
	while (ft_isspace(*cpy))
		cpy++;
	if (check_instructions(cpy))
		invalid_ins_sim(arr, cpy, mod);
	if (*cpy != DIRECT_CHAR)
		invalid_instruction(0, g_op[mod - 1]);
	command = (t_command*)ft_memalloc(sizeof(t_command));
	command->name = mod;
	command->command = str;
	command->byte_size = mod == 1 ? 5 : 3;
	ft_list_push_back(&head->list, command);
}

void		c_ld_lld(char *str, t_head *head, int mod, int *arr)
{
	t_command	*command;
	char		*cpy;
	int			byte_size;

	cpy = str + ft_strlen(g_op[mod - 1]);
	while (ft_isspace(*cpy))
		cpy++;
	if (check_instructions(cpy))
		invalid_ins_sim(arr, cpy, mod);
	if (*cpy != DIRECT_CHAR && *cpy != ' ' && !(*cpy >= '0' && *cpy <= '9') && *cpy != LABEL_CHAR)
		invalid_instruction(0, g_op[mod - 1]);
	byte_size = 3 + (*cpy == DIRECT_CHAR ? 4 : 2);
	while (*cpy != SEPARATOR_CHAR && *cpy)
		cpy++;
	if (!*cpy)
		invalid_instruction(1, g_op[mod - 1]);
	cpy++;
	while (ft_isspace(*cpy))
		cpy++;
	if (*cpy != 'r')
		invalid_instruction(1, g_op[mod - 1]);
	command = (t_command*)ft_memalloc(sizeof(t_command));
	command->name = mod;
	command->command = str;
	command->byte_size = byte_size;
	ft_list_push_back(&head->list, command);
}

void		c_and_xor_or(char *str, t_head *head, int mod, int *arr)
{
	t_command	*command;
	char		*cpy;
	int			temp;
	int			byte_size;

	cpy = str + ft_strlen(g_op[mod - 1]);
	while (ft_isspace(*cpy))
		cpy++;
	if (check_instructions(cpy))
		invalid_ins_sim(arr, cpy, mod);
	if ((temp = instruction_size(*cpy, 4)))
		byte_size = temp;
	else
		invalid_instruction(0, g_op[mod - 1]);
	while (*cpy != SEPARATOR_CHAR && *cpy )
		cpy++;
	if (!*cpy)
		invalid_instruction(1, g_op[mod - 1]);
	cpy++;
	while (ft_isspace(*cpy))
		cpy++;
	if ((temp = instruction_size(*cpy, 4)))
		byte_size += temp;
	else
		invalid_instruction(1, g_op[mod - 1]);
	while (*cpy != SEPARATOR_CHAR && *cpy)
		cpy++;
	if (!*cpy)
		invalid_instruction(2, g_op[mod - 1]);
	cpy++;
	while (ft_isspace(*cpy))
		cpy++;
	if ((temp = instruction_size(*cpy, 4)))
		byte_size += temp + 2;
	else
		invalid_instruction(2, g_op[mod - 1]);
	command = (t_command*)ft_memalloc(sizeof(t_command));
	command->name = mod;
	command->command = str;
	command->byte_size = byte_size;
	ft_list_push_back(&head->list, command);
}

void		c_add_sub(char *str, t_head *head, int mod, int *arr)
{
	t_command	*command;
	char		*cpy;

	cpy = str + ft_strlen(g_op[mod - 1]);
	while (ft_isspace(*cpy))
		cpy++;
	if (check_instructions(cpy))
		invalid_ins_sim(arr, cpy, mod);
	if (*cpy != 'r')
		invalid_instruction(0, g_op[mod - 1]);
	while (*cpy != SEPARATOR_CHAR && *cpy)
		cpy++;
	if (!*cpy)
		invalid_instruction(1, g_op[mod - 1]);
	cpy++;
	while (ft_isspace(*cpy))
		cpy++;
	if (*cpy != 'r')
		invalid_instruction(1, g_op[mod - 1]);
	while (*cpy != SEPARATOR_CHAR && *cpy)
		cpy++;
	if (!*cpy)
		invalid_instruction(2, g_op[mod - 1]);
	cpy++;
	while (ft_isspace(*cpy))
		cpy++;
	if (*cpy != 'r')
		invalid_instruction(2, g_op[mod - 1]);
	command = (t_command*)ft_memalloc(sizeof(t_command));
	command->name = mod;
	command->command = str;
	command->byte_size = 5;
	ft_list_push_back(&head->list, command);
}

void		c_ldi_lldi(char *str, t_head *head, int mod, int *arr)
{
	t_command	*command;
	char		*cpy;
	int			temp;
	int			byte_size;

	cpy = str + ft_strlen(g_op[mod - 1]);
	while (ft_isspace(*cpy))
		cpy++;
	if (check_instructions(cpy))
		invalid_ins_sim(arr, cpy, mod);
	if ((temp = instruction_size(*cpy, 2)))
		byte_size = temp;
	else
		invalid_instruction(0, g_op[mod - 1]);
	while (*cpy != SEPARATOR_CHAR && *cpy )
		cpy++;
	if (!*cpy)
		invalid_instruction(1, g_op[mod - 1]);
	cpy++;
	while (ft_isspace(*cpy))
		cpy++;
	if ((temp = instruction_size(*cpy, 2)))
		byte_size += temp;
	else
		invalid_instruction(1, g_op[mod - 1]);
	while (*cpy != SEPARATOR_CHAR && *cpy)
		cpy++;
	if (!*cpy)
		invalid_instruction(2, g_op[mod - 1]);
	cpy++;
	while (ft_isspace(*cpy))
		cpy++;
	if ((temp = instruction_size(*cpy, 2)))
		byte_size += temp + 2;
	else if (temp == 0 || temp == 1)
		invalid_instruction(2, g_op[mod - 1]);
	command = (t_command*)ft_memalloc(sizeof(t_command));
	command->name = mod;
	command->command = str;
	command->byte_size = byte_size;
	ft_list_push_back(&head->list, command);
}

void		c_st(char *str, t_head *head, int mod, int *arr)
{
	t_command	*command;
	char		*cpy;
	int			byte_size;

	cpy = str + ft_strlen(g_op[mod - 1]);
	while (ft_isspace(*cpy))
		cpy++;
	if (check_instructions(cpy))
		invalid_ins_sim(arr, cpy, mod);
	if (*cpy != 'r')
		invalid_instruction(0, g_op[mod - 1]);
	while (*cpy != SEPARATOR_CHAR && *cpy )
		cpy++;
	if (!*cpy)
		invalid_instruction(1, g_op[mod - 1]);
	cpy++;
	while (ft_isspace(*cpy))
		cpy++;
	if (*cpy == DIRECT_CHAR)
		invalid_instruction(1, g_op[mod - 1]);
	byte_size = 3 + (*cpy == 'r' ? 1 : 2);
	command = (t_command*)ft_memalloc(sizeof(t_command));
	command->name = mod;
	command->command = str;
	command->byte_size = byte_size;
	ft_list_push_back(&head->list, command);
}

void		c_sti(char *str, t_head *head, int mod, int *arr)
{
	t_command	*command;
	char		*cpy;
	int			byte_size;
	int			temp;

	cpy = str + ft_strlen(g_op[mod - 1]);
	while (ft_isspace(*cpy))
		cpy++;
	if (check_instructions(cpy))
		invalid_ins_sim(arr, cpy, mod);
	if (*cpy != 'r')
		invalid_instruction(0, g_op[mod - 1]);
	while (*cpy != SEPARATOR_CHAR && *cpy )
		cpy++;
	if (!*cpy)
		invalid_instruction(1, g_op[mod - 1]);
	cpy++;
	while (ft_isspace(*cpy))
		cpy++;
	if ((temp = instruction_size(*cpy, 2)))
		byte_size = temp + 3;
	while (*cpy != SEPARATOR_CHAR && *cpy)
		cpy++;
	if (!*cpy)
		invalid_instruction(2, g_op[mod - 1]);
	cpy++;
	while (ft_isspace(*cpy))
		cpy++;
	if (*cpy != DIRECT_CHAR && *cpy != 'r')
		invalid_instruction(2, g_op[mod - 1]);
	if (*cpy == 'r')
		byte_size += 1;
	else
		byte_size += 2;
	command = (t_command*)ft_memalloc(sizeof(t_command));
	command->name = mod;
	command->command = str;
	command->byte_size = byte_size;
	ft_list_push_back(&head->list, command);
}

void		c_aff(char *str, t_head *head, int mod, int *arr)
{
	t_command	*command;
	char		*cpy;

	cpy = str + ft_strlen(g_op[mod - 1]);
	while (ft_isspace(*cpy))
		cpy++;
	if (check_instructions(cpy))
		invalid_ins_sim(arr, cpy, mod);
	if (*cpy != 'r')
		invalid_instruction(0, g_op[mod - 1]);
	command = (t_command*)ft_memalloc(sizeof(t_command));
	command->name = mod;
	command->command = str;
	command->byte_size = 3;
	ft_list_push_back(&head->list, command);
}