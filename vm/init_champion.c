/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_champion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoughnu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 14:43:36 by sdoughnu          #+#    #+#             */
/*   Updated: 2020/01/13 14:43:46 by sdoughnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void	read_name(t_champion *ch, int fd)
{
	int		i;
	char 	c;

	i = -1;
	while (++i < PROG_NAME_LENGTH)
		read(fd, &(ch->name[i]), 1);
	i = 0;
	while (++i < 5)
		read(fd, &c, 1);
//	printf("%s\n", ch->name);
}

int		read_size(fd)
{
	t_4bytes		num;
	unsigned int	c;

	read(fd, &c, 4);
	num.hex = c;
	num.field.o_temp = num.field.octet1;
	num.field.octet1 = num.field.octet4;
	num.field.octet4 = num.field.o_temp;
	num.field.o_temp = num.field.octet2;
	num.field.octet2 = num.field.octet3;
	num.field.octet3 = num.field.o_temp;
//	printf("\n----------%0.8x\n", num.hex);
//	printf("\n----------%d\n", num.hex);
	return (num.hex);
}

void	read_com(t_champion *ch, int fd)
{
	int		i;
	char 	c;

	i = -1;
	while (++i < COMMENT_LENGTH)
		read(fd, &(ch->com[i]), 1);
	i = -1;
	while (++i < 4)
		read(fd, &c, 1);
//	printf("%s\n", ch->com);
}

int		read_code(int fd, t_champion *ch)
{
	int i;

	i = -1;
	if (!(ch->code = (char*)malloc(sizeof(char) * (ch->size + 1))))
		return (printf("%s", "Memory not allocated\n") - 21);
	while (++i < ch->size)
		read(fd, &(ch->code[i]), 1);
//	i = -1;
//	while (++i < ch->size)
//		printf("%c ", ch->code[i]);
	return (1);
}

int 	init_champ(int *i, char **av, int n, t_vm *vm)
{
	t_champion		*ch;
	int				fd;

	if ((fd = open(av[*i], O_RDONLY)) < 0)
		return (printf("Can't open file...\n") - 19);
//	printf("%d\n", fd);
	if (!exec_magic(fd))
		return (printf("Corewar_exec_magic doesn't match\n") - 33);
	if (!(ch = (t_champion*)malloc(sizeof(t_champion))))
		return (printf("Memory not allocated\n") - 21);
	ch->n = 0;
	read_name(ch, fd);
	if ((ch->size = read_size(fd)) > CHAMP_MAX_SIZE)
		return (printf("Big champion exec code size\n") - 28);
	read_com(ch, fd);
	if (!read_code(fd, ch))
		return (0);
	close(fd);
	champ_in_vm(ch, vm, n);
	(*i)++;
	vm->players += 1;
	return (1);
}
