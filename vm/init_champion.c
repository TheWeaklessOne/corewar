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

	if (!(read(fd, ch->name, PROG_NAME_LENGTH)))
		exit(!printf("Read error"));
	ch->name[PROG_NAME_LENGTH] = '\0';
	i = -1;
	while (++i < 4)
		read(fd, &c, 1);
}

unsigned int		read_size(fd)
{
	t_4bytes		num;
	unsigned int	c;
	unsigned char	tmp;

	read(fd, &c, 4);
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

	if (!(read(fd, ch->com, COMMENT_LENGTH)))
		exit(!printf("Read error\n"));
	ch->com[COMMENT_LENGTH] = '\0';
	i = -1;
	while (++i < 4)
		read(fd, &c, 1);
}

int					read_code(int fd, t_champion *ch)
{
	if (!(ch->code = (char*)malloc(sizeof(char) * (ch->size + 1))))
		return (!printf("%s", "Memory not allocated\n"));
	if (!(read(fd, ch->code, ch->size)))
		return (!printf("Read error\n"));
	ch->code[ch->size] = '\0';
	return (1);
}

int					init_champ(int *i, char **av, int n, t_vm *vm)
{
	t_champion		*ch;
	int				fd;

	vm->players += 1;
	if (vm->players > MAX_PLAYERS)
		return (!printf("Too much champions\n"));
	if (!check_ch_name(av, *i))
		return (!ft_printf("You gave not a *.cor file - %s\n", av[*i]));
	if ((fd = open(av[*i], O_RDONLY)) < 0)
		return (!ft_printf("Can't open file %s\n", av[*i]));
	if (!exec_magic(fd))
		return (!ft_printf("Corewar_exec_magic doesn't match - %s\n", av[*i]));
	if (!(ch = (t_champion*)malloc(sizeof(t_champion))))
		return (!printf("Memory not allocated\n"));
	ch->n = 0;
	read_name(ch, fd);
	if ((ch->size = read_size(fd)) > CHAMP_MAX_SIZE)
		return (!ft_printf("Big champion exec code size - %s\n", av[*i]));
	read_com(ch, fd);
	if (!read_code(fd, ch))
		return (0);
	close(fd);
	champ_in_vm(ch, vm, n);
	(*i)++;
	return (1);
}
