/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembly_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stross <stross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 14:39:11 by stross            #+#    #+#             */
/*   Updated: 2020/02/18 11:48:42 by stross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	write_exec_code_help(t_4bytes num, unsigned char octet, int fd)
{
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
}

void	write_exec_code(int size, int fd)
{
	t_4bytes		num;
	unsigned char	octet;

	num.hex = size;
	octet = 0;
	write_exec_code_help(num, octet, fd);
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

static void	null_vars(int *len, int *i, int *size)
{
	*len = 0;
	*size = 0;
	*i = 0;
}

void create_struct(t_head *head)
{
	int			len;
	int			i;
	int			size;
	t_asm_list	*list;

	list = head->list;
	null_vars(&len, &i, &size);
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