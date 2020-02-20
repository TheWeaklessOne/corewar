/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_champion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoye <djoye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 14:43:36 by sdoughnu          #+#    #+#             */
/*   Updated: 2020/01/24 17:58:20 by djoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void				read_name(t_champion *ch, int fd)
{
	int				i;
	char			c;

	if (read(fd, ch->name, PROG_NAME_LENGTH) <= 0)
		exit(print_fd("Read champion name error\n", 2));
	ch->name[PROG_NAME_LENGTH] = '\0';
	i = -1;
	while (++i < 4)
		read(fd, &c, 1);
}

unsigned int		read_size(int fd)
{
	t_4bytes		num;
	unsigned int	c;
	unsigned char	tmp;

	if (read(fd, &c, 4) <= 0)
		exit(print_fd("Read champion exec code size error\n", 2));
	num.hex = c;
	tmp = num.f.o1;
	num.f.o1 = num.f.o4;
	num.f.o4 = tmp;
	tmp = num.f.o2;
	num.f.o2 = num.f.o3;
	num.f.o3 = tmp;
	return (num.hex);
}

void				read_com(t_champion *ch, int fd)
{
	int				i;
	char			c;

	if (read(fd, ch->com, COMMENT_LENGTH) <= 0)
		exit(print_fd("Read error\n", 2));
	ch->com[COMMENT_LENGTH] = '\0';
	i = -1;
	while (++i < 4)
		read(fd, &c, 1);
}

int					read_code(int fd, t_champion *ch)
{
	if (!(ch->code = (char*)malloc(sizeof(char) * (ch->size + 1))))
		return (print_fd("Memory not allocated\n", 2));
	if (read(fd, ch->code, ch->size) != ch->size)
		return (print_fd("Champion size error (too small) ", 2));
	if (read(fd, NULL, 1))
		return (print_fd("Champion size error (too big) ", 2));
	ch->code[ch->size] = '\0';
	return (1);
}

int					init_champ(int *i, char **av, int n, t_vm *vm)
{
	t_champion		*ch;
	int				fd;

	vm->players += 1;
	if (vm->players > MAX_PLAYERS)
		return (print_fd("Too much champions\n", 2));
	if (!check_ch_name(av, *i))
		return (error_in("You gave not a *.cor file - ", av[*i], 2));
	if ((fd = open(av[*i], O_RDONLY)) < 0)
		return (error_in("Can't open file ", av[*i], 2));
	if (!exec_magic(fd))
		return (error_in("Corewar_exec_magic doesn't match - ", av[*i], 2));
	if (!(ch = (t_champion*)malloc(sizeof(t_champion))))
		return (print_fd("Memory not allocated\n", 2));
	ch->n = 0;
	read_name(ch, fd);
	if ((ch->size = read_size(fd)) > CHAMP_MAX_SIZE)
		return (error_in("Different champion exec code size - ", av[*i], 2));
	read_com(ch, fd);
	if (!read_code(fd, ch))
		return (print_fd2(av[*i], 2));
	close(fd);
	champ_in_vm(ch, vm, n);
	(*i)++;
	return (1);
}
