/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoughnu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 11:39:19 by sdoughnu          #+#    #+#             */
/*   Updated: 2020/01/15 11:39:32 by sdoughnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int 	exec_magic(int fd)
{
	t_4bytes		num;
	unsigned int	c;

	read(fd, &c, 4);
//	printf("%x\n", c);
	num.hex = c;
	num.field.o_temp = num.field.octet1;
	num.field.octet1 = num.field.octet4;
	num.field.octet4 = num.field.o_temp;
	num.field.o_temp = num.field.octet2;
	num.field.octet2 = num.field.octet3;
	num.field.octet3 = num.field.o_temp;
//	printf("\n----------%0.8x\n", num.hex);
	if (num.hex == COREWAR_EXEC_MAGIC)
		return (1);
	return (0);
}

void		champ_in_vm(t_champion *ch, t_vm *vm, int n)
{
	int			i;
	t_champion	*buf;

	i = 0;
	buf = NULL;
	if (n < 0)
	{
		while (i < MAX_PLAYERS && vm->champ[i])
			i++;
		vm->champ[i] = ch;
	}
	else
	{
		if (vm->champ[n - 1])
			buf = vm->champ[n - 1];
		vm->champ[n - 1] = ch;
		while (i < MAX_PLAYERS && vm->champ[i])
			i++;
		vm->champ[i] = buf;
	}
}
