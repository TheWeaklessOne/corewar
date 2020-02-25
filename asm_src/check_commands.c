/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoye <djoye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 15:38:18 by stross            #+#    #+#             */
/*   Updated: 2020/02/25 17:46:17 by djoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		create_command(char *str, int mod, int byte_size, t_head *head)
{
	t_command	*command;

	command = (t_command*)ft_memalloc(sizeof(t_command));
	command->name = mod;
	command->command = str;
	command->byte_size = byte_size;
	ft_list_push_back(&head->list, command);
}

int			instruction_size(char ch, int size)
{
	if (ch == 'r')
		return (1);
	else if (ch == ' ' || (ch >= '0' && ch <= '9') ||
	ch == LABEL_CHAR || ch == '-')
		return (2);
	else if (ch == '%')
		return (size);
	else
		return (0);
}

int			check_instructions(char *str)
{
	int		i;

	i = 0;
	while (*str)
	{
		if (*str == LABEL_CHAR)
		{
			while (*str && *str != ' ' &&
			*str != SEPARATOR_CHAR && *str != DIRECT_CHAR)
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
	int			byte_size;
	char		*cpy;

	cpy = str + ft_strlen(g_op[mod - 1]);
	while (ft_isspace(*cpy))
		cpy++;
	if (check_instructions(cpy))
		invalid_ins_sim(arr, cpy, mod);
	if (*cpy != DIRECT_CHAR)
		invalid_instruction(0, g_op[mod - 1]);
	byte_size = mod == 1 ? 5 : 3;
	check_after_arg(g_op[mod - 1], cpy);
	create_command(str, mod, byte_size, head);
}

void		c_ld_lld(char *str, t_head *head, int mod, int *arr)
{
	char		*cpy;
	int			byte_size;

	cpy = str + ft_strlen(g_op[mod - 1]);
	while (ft_isspace(*cpy))
		cpy++;
	if (check_instructions(cpy))
		invalid_ins_sim(arr, cpy, mod);
	if (*cpy != DIRECT_CHAR && *cpy != ' ' &&
	!(*cpy >= '0' && *cpy <= '9') && *cpy != LABEL_CHAR && *cpy != '-')
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
	check_after_arg(g_op[mod - 1], cpy);
	create_command(str, mod, byte_size, head);
}
