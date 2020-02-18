/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stross <stross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 13:38:54 by stross            #+#    #+#             */
/*   Updated: 2020/02/18 11:49:12 by stross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	write_magic(int fd)
{
	int			magic_num;
	t_4bytes	num;

	magic_num = COREWAR_EXEC_MAGIC;
	num.hex = magic_num;
	num.field.o_temp = num.field.octet1;
	num.field.octet1 = num.field.octet4;
	num.field.octet4 = num.field.o_temp;
	num.field.o_temp = num.field.octet2;
	num.field.octet2 = num.field.octet3;
	num.field.octet3 = num.field.o_temp;
	write(fd, &num.hex, 4);
}

static void	write_commands(int fd, t_command **commands)
{
	int		i;

	i = 0;
	while (commands[i])
	{
		if (commands[i]->is_label == false)
			write_command(fd, commands[i], commands);
		i++;
	}
}

void	assembly(int fd, t_head *head)
{
	write_magic(fd);
	write(fd, head->name, PROG_NAME_LENGTH);
	write(fd, "\0\0\0\0", 4);
	create_struct(head);
	write_exec_code(head->exec_size, fd);
	write(fd, head->comment, COMMENT_LENGTH);
	write(fd, "\0\0\0\0", 4);
	write_commands(fd, head->commands);
	free(head->main_str);
	free(head->split_str); //FIXME for my shitty split
//	free_split(head->split_str); //FIXME for ft_split
	if ((close(fd)) == -1)
	{
		write(2, "Failed to close file\n", 22);
		exit(1);
	}
}