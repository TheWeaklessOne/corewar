/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoye <djoye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 13:12:22 by sdoughnu          #+#    #+#             */
/*   Updated: 2020/01/20 16:09:09 by djoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int		position(t_vm *vm, int player, int i)
{
	int c;

	c  = -1;
	if (vm->champ[player] == NULL)
		return (printf("You enter the flag [-n] incorrectly .-.\n") - 40);
	while (++c < vm->champ[player]->size)
	{
		vm->arena[i] = vm->champ[player]->code[c];
		vm->map_color[i] = player + 1;
		i++;
	}
	return (1);
}

void	print_arena(t_vm *vm, int step)
{
	int i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i == 0 || (i % 32) == 0)
			printf("0x%0.4x : ", i);
		if (vm->color == 1 && vm->map_color[i] == 1)
			printf("\e[31m%0.2x", vm->arena[i]);
		else if (vm->color == 1 && vm->map_color[i] == 2)
			printf("\e[32m%0.2x", vm->arena[i]);
		else if (vm->color == 1 && vm->map_color[i] == 3)
			printf("\e[33m%0.2x", vm->arena[i]);
		else if (vm->color == 1 && vm->map_color[i] == 4)
			printf("\e[34m%0.2x", vm->arena[i]);
		else
			printf("\e[0m%0.2x", vm->arena[i]);
		if ((i + 1) % 32 == 0 && i != 0)
			printf("\e[0m\n");
		else printf("\e[0m ");
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
	{
		vm->arena[i] = 0;
		vm->map_color[i] = 0;
	}	
	step = MEM_SIZE / vm->players;
	player = 0;
	i = 0;
	while (player < vm->players)
	{
		if (!position(vm, player, i))
			return (0);
		i = i + step;
		player++;
	}
	print_arena_test(vm, step);
	//print_arena(vm, step);
	return (1);
}
