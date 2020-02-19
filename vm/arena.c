/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoye <djoye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 13:12:22 by sdoughnu          #+#    #+#             */
/*   Updated: 2020/01/22 18:09:37 by djoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int				position(t_vm *vm, int player, int i)
{
	unsigned int			c;

	c = -1;
	if (vm->champ[player] == NULL)
		return (print_fd("You enter the flag [-n] incorrectly .-.\n", 2));
	while (++c < vm->champ[player]->size)
	{
		vm->arena[i] = vm->champ[player]->code[c];
		vm->map_color[i] = player + 1;
		i++;
	}
	return (1);
}

int				print_arena(t_vm *vm, int size)
{
	int			i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i == 0 || (i % size) == 0)
			ft_printf("0x%0.4x : ", i);
		ft_printf("%0.2x ", (unsigned char)vm->arena[i]);
		if (((i + 1) % size == 0) && i != 0)
			write(1, "\n", 1);
		i++;
	}
	return (0);
}

int				build_arena(t_vm *vm)
{
	int			i;
	int			player;
	const int	step = MEM_SIZE / vm->players;

	i = -1;
	while (++i < MEM_SIZE)
	{
		vm->arena[i] = 0;
		vm->map_color[i] = 0;
	}
	player = 0;
	i = 0;
	while (player < vm->players)
	{
		if (!position(vm, player, i))
			return (0);
		i += step;
		player++;
	}
	return (1);
}
