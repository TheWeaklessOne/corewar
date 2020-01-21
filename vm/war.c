/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   war.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoughnu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 10:48:04 by sdoughnu          #+#    #+#             */
/*   Updated: 2020/01/20 10:48:05 by sdoughnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int 	war_coming(t_vm *vm)
{
	int step;

	step = MEM_SIZE / vm->players;
//	while (vm->global)
//	{
//		if (vm->d != -1 && )
//	}
	if (vm->dump != -1)
		print_arena(vm, step, 32);
	else if (vm->d != -1)
		print_arena(vm, step, 64);
	else if (vm->color == 1)
		print_arena_test(vm, step);
	return (1);
}
