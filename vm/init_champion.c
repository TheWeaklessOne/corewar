/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_champion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoughnu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 14:43:36 by sdoughnu          #+#    #+#             */
/*   Updated: 2020/01/14 19:19:38 by stross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

typedef struct	s_bit_field
{
	int			octet1 : 8;
	int			octet2 : 8;
	int			octet3 : 8;
	int			octet4 : 8;
	int			o_temp : 8;
}				t_bit_field;

typedef	union	u_4bytes
{
	t_bit_field field;
	int			hex;
}				t_4bytes;

int 	exec_magic(int fd)
{
	t_4bytes		num;
	unsigned int	c;

	read(fd, &c, 4);
	printf("%x\n", c);
	num.hex = c;
	num.field.o_temp = num.field.octet1;
	num.field.octet1 = num.field.octet4;
	num.field.octet4 = num.field.o_temp;
	num.field.o_temp = num.field.octet2;
	num.field.octet2 = num.field.octet3;
	num.field.octet3 = num.field.o_temp;
	printf("\n----------%0.8x\n", num.hex);
	if (num.hex == COREWAR_EXEC_MAGIC)
	{
		puts("ok");
		return (0);
	}
	return (1);
}

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
	printf("\n%s\n", ch->name);
}

int32_t	read_size(fd)
{
	int i;

	i = -1;
	char c;

	while (++i < 4)
		read(fd, &c, 1);
	/*
	 *
	 */
	return (22);
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
	printf("%s\n", ch->com);
}

void	read_code(int fd, t_champion *ch)
{
	int i;

	i = -1;
	ch->code = (char *)malloc(sizeof(char) * (ch->size + 1));
	while (++i < ch->size)
		read(fd, &(ch->code[i]), 1);
	i = -1;
	while (++i < ch->size)
	{
		printf("%c ", ch->code[i]);
	}
}

int 	init_champ(int *i, char **av, int n, t_vm *vm)
{
	t_champion		*ch;
	int				fd;

	if ((fd = open(av[*i], O_RDONLY)) < 0)
		return (printf("%s", "Can't open file...\n") - 19);
	printf("%d\n", fd);
	if (!exec_magic(fd))
		return (printf("%s", "Corewar_exec_magic doesn't match\n") - 33);
	if (!(ch = (t_champion*)malloc(sizeof(t_champion))))
		return (printf("%s", "Memory not allocated\n") - 21);
	read_name(ch, fd);
	if ((ch->size = read_size(fd)) > CHAMP_MAX_SIZE)
		return (printf("%s", "Big champion exec code size\n") - 28);
	read_com(ch, fd);
	printf("%x\n", COREWAR_EXEC_MAGIC);
	int ip = -1;
	char c;
//	while (++ip < 30)
//	{
//		read(fd, &c, 1);
//		printf("%c ", c);
//	}
	read_code(fd, ch);
	close(fd);
	(*i)++;
	return (1);
}
