/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stross <stross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 17:53:29 by stross            #+#    #+#             */
/*   Updated: 2020/02/25 13:28:36 by stross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		write_command_code(int fd, int name)
{
	unsigned char	octet;
	static int		arr[16] = { 1, 16, 11, 4, 5, 6, 7, 8, 9, 10, 3,
						12, 14, 13, 15, 2 };

	octet = arr[name - 1];
	write(fd, &octet, 1);
}

static void	null_vars(t_label *l)
{
	l->equ = false;
	l->i = 0;
	l->lab = 0;
	l->dist = 0;
}

int			get_label_distance(t_command *command,
		t_command **commands, char *label, int *mod)
{
	t_label	l;

	null_vars(&l);
	while (commands[l.i])
	{
		if (command == commands[l.i])
			l.comm = l.i;
		if (ft_strequ(label, commands[l.i]->label))
		{
			l.lab = l.i;
			l.equ = true;
		}
		l.i++;
	}
	if (!l.equ)
		no_label_error();
	if (l.lab > l.comm)
		norm_get_label(&l, mod, commands);
	else if (l.lab < l.comm)
		norm_get_label2(&l, mod, commands);
	else
		return (-1);
	free(label);
	return (l.dist);
}

static void	write_live(int fd, t_command *command, t_command **commands)
{
	char	*str;
	int		dist;
	int		mod;

	str = command->command;
	write(fd, &command->name, 1);
	while (*str && *str != DIRECT_CHAR)
		str++;
	str++;
	if (*str == LABEL_CHAR)
	{
		dist = get_label_distance(command, commands, get_comm_label(str), &mod);
		if (dist == -1)
			no_label_error();
		if (mod == 2)
			dist = ~dist + 1;
		write_exec_code(dist, fd);
	}
	else
	{
		dist = ft_atoi(str);
		write_exec_code(dist, fd);
	}
}

void		write_command(int fd, t_command *command, t_command **commands)
{
	if (command->name == 1)
		write_live(fd, command, commands);
	else
	{
		write_command_code(fd, command->name);
		if (command->name != 9 && command->name != 12
		&& command->name != 15 && command->name != 0)
			write_arg_type(command->command, fd, command->name);
		if (command->name == 9 || command->name == 10
		|| command->name == 3 || command->name == 12
		|| command->name == 13 || command->name == 15)
			main_write(fd, command, commands, 2);
		else
			main_write(fd, command, commands, 4);
	}
}
