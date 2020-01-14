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

int 	exec_magic(int fd)
{
	int i;
	unsigned char	e;
	unsigned int	c;
	unsigned int	tmp;
	int				x = 0x1 << 31;


	i = -1;
	read(fd, &c, 4);
	printf("orig%x\n", c);
	tmp = c;
	//c = (tmp << 24 | tmp << 16 | tmp >> 16 | tmp >> 24);
	if (x & c)
	{

	}
	printf("%x\n", c);
	/*while (++i < 4)
	{
		read(fd, &c, 1);
		printf("%x", c);
	}*/
//	if (c != COREWAR_EXEC_MAGIC)
//		return (0);
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
