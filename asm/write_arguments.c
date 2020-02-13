/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stross <stross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 17:40:19 by stross            #+#    #+#             */
/*   Updated: 2020/02/11 18:15:55 by stross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	handle_dir(int fd, char *str, t_command *command, t_command **commands)
{
	int		num;
	int		mod;

	if (*str == DIRECT_CHAR)
		str++;
	if (*str == LABEL_CHAR)
	{
		num = get_label_distance(command, commands, get_comm_label(str), &mod);
		if (num == -1)
			no_label_error();
		if (mod == 2)
			num = ~num + 1;
		write_exec_code(num, fd);
	}
	else
	{
		num = ft_atoi(str);
		write_exec_code(num, fd);
	}
}

void	handle_dir_2size(int fd, char *str, t_command *command, t_command **commands)
{
	int		num;
	int		mod;

	if (*str == DIRECT_CHAR)
		str++;
	if (*str == LABEL_CHAR)
	{
		num = get_label_distance(command, commands, get_comm_label(str), &mod);
		if (num == -1)
			no_label_error();
		if (mod == 2)
			num = ~num + 1;
		write_exec_code_2b(num, fd);
	}
	else
	{
		num = ft_atoi(str);
		write_exec_code_2b(num, fd);
	}
}

void	write_reg(int fd, char *str)
{
	unsigned char	oct;

	if (*str == 'r')
		str++;
	oct = ft_atoi(str);
	write(fd, &oct, 1);
}