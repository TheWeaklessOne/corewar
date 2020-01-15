/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoughnu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 13:12:22 by sdoughnu          #+#    #+#             */
/*   Updated: 2020/01/15 13:12:24 by sdoughnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void		position(t_vm *vm, int player, int i)
{
	int c;

	c  = -1;
	while (++c < vm->champ[player]->size)
	{
//		printf("%d\n", i);
		vm->arena[i] = vm->champ[player]->code[c];
//		printf("%0.2x | %0.2x\n", vm->arena[i], vm->champ[player]->code[c]);
		i++;
	}
}

void	print_arena(t_vm *vm, int step)
{
	int i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i == 0 || (i % 32) == 0)
			printf("0x%0.4x : ", i);
		printf("%0.2x", vm->arena[i]);
		if ((i + 1) % 32 == 0 && i != 0)
			printf("\n");
		else printf(" ");
		i++;
	}
}

int 	build_arena(t_vm *vm)
{
	int	i;
	int player;
	int step;

	i = -1;
	while (++i < MEM_SIZE)
		vm->arena[i] = '\0';
	step = MEM_SIZE / vm->players;
	player = 0;
	i = 0;
	while (player < vm->players)
	{
		position(vm, player, i);
		i = i + step;
		player++;
	}
	print_arena(vm, step);
	return (1);
}
