/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stross <stross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 17:53:29 by stross            #+#    #+#             */
/*   Updated: 2020/02/11 14:38:37 by stross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		write_command_code(int fd, int name)
{
	unsigned char	octet;
	static int	arr[16] = { 1, 16, 11, 4, 5, 6 ,7 ,8, 9, 10, 3, 12, 14, 13, 15, 2 };

	octet = arr[name - 1];
	printf("%d", octet);
	write(fd, &octet, 1);
}

int			get_label_distance(t_command *command, t_command **commands, char *label, int *mod)
{
	int		lab;
	int		comm;
	int		dist;
	int		i;

	i = 0;
	lab = -1;
	dist = 0;
	while (commands[i])
	{
		if (command == commands[i])
			comm = i;
		if (ft_strequ(label, commands[i]->label))
			lab = i;
		i++;
	}
	if (lab > comm)
	{
		while (comm <= lab)
		{
			comm++;
			dist += commands[comm]->byte_size;
		}
		*mod = 1; //POSITIVE
	}
	else if (lab < comm)
	{
		while (comm > lab + 1)
		{
			lab++;
			dist += commands[lab]->byte_size;
		}
		*mod = 2; // NEGATIVE
	}
	free(label);
	return (dist);
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
		if (command->name != 9 && command->name != 12 && command->name != 15)

	}
}