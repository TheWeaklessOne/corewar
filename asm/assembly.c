/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stross <stross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 13:38:54 by stross            #+#    #+#             */
/*   Updated: 2020/02/10 19:28:47 by stross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	write_exec_code(int size, int fd)
{
	t_4bytes		num;
	unsigned char	octet;

	num.hex = size;
	if (num.field.octet4 == 0)
		write(fd, "\0", 1);
	else
	{
		octet = num.field.octet4;
		write(fd, &octet, 1);
	}
	if (num.field.octet3 == 0)
		write(fd, "\0", 1);
	else
	{
		octet = num.field.octet3;
		write(fd, &octet, 1);
	}
	if (num.field.octet2 == 0)
		write(fd, "\0", 1);
	else
	{
		octet = num.field.octet2;
		write(fd, &octet, 1);
	}
	if (num.field.octet1 == 0)
		write(fd, "\0", 1);
	else
	{
		octet = num.field.octet1;
		write(fd, &octet, 1);
	}
}

static void create_struct(t_head *head)
{
	int			len;
	int			i;
	int			size;
	t_asm_list	*list;

	list = head->list;
	len = 0;
	size = 0;
	i = 0;
	while (list)
	{
		size += list->command->byte_size;
		list->command->total_bytes = size;
		len++;
		list = list->next;
	}
	head->commands = (t_command**)ft_memalloc((len + 1) * sizeof(t_command*));
	list = head->list;
	while (list)
	{
		head->commands[i] = list->command;
		i++;
		list = list->next;
	}
	ft_list_clear(&head->list);
	head->exec_size = size;
}

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
	free(head->split_str);
	if ((close(fd)) == -1)
	{
		write(2, "Failed to close file\n", 22);
		exit(1);
	}
}