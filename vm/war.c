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

//void	skip_bytes(unsigned char arg)
//{
//
//}

void 	cycle(t_vm *vm, t_op *op_tab)
{
	t_cur	*buf;
	int		i;

	buf = vm->curs;
	while (buf->next->next)
		buf = buf->next;
	i = buf->pos + vm->champ[buf->id]->size;
	while (buf->pos < i)
	{
		if (vm->arena[buf->pos] >= 1 && vm->arena[buf->pos] <= 16)
		{
			if (check_arg(op_tab, vm->arena[buf->pos], vm->arena[buf->pos + 1]))
			{
				printf("Valid operation\n");
				//skip_bytes(vm->arena[buf->pos + 1]);
				buf->pos += 2;
			}
			else
			{
				printf("...\n");
				buf->pos += 1;
			}
		}
		else
			buf->pos += 1;
	}
}

int 	war_coming(t_vm *vm)
{
	int step;
	t_op    op_tab[17] =
			{
					{"live",	1, {T_DIR},												  1, 10, "alive", 0, 0},
					{"ld",		2, {T_DIR | T_IND, T_REG}, 								  2, 5, "load", 1, 0},
					{"st",		2, {T_REG, T_IND | T_REG}, 								  3, 5, "store", 1, 0},
					{"add",		3, {T_REG, T_REG, T_REG}, 							      4, 10, "addition", 1, 0},
					{"sub",		3, {T_REG, T_REG, T_REG}, 								  5, 10, "soustraction", 1, 0},
					{"and",		3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6, "et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
					{"or",		3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,	"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
					{"xor",		3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,	"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
					{"zjmp",	1, {T_DIR}, 											  9, 20, "jump if zero", 0, 1},
					{"ldi",		3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 		  10, 25,"load index", 1, 1},
					{"sti",		3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},		  11, 25, "store index", 1, 1},
					{"fork",	1, {T_DIR},												  12, 800, "fork", 0, 1},
					{"lld",		2, {T_DIR | T_IND, T_REG},								  13, 10, "long load", 1, 0},
					{"lldi",	3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},         14, 50, "long load index", 1, 1},
					{"lfork",	1, {T_DIR},												  15, 1000, "long fork", 0, 1},
					{"aff",		1, {T_REG},												  16, 2, "aff", 1, 0},
					{0, 0, {0}, 0, 0, 0, 0, 0}
			};

	step = MEM_SIZE / vm->players;
	vm->check = 1;
	while (vm->check)
	{
		if (vm->d == vm->global)
			print_arena(vm, step, 64);
		if (vm->dump == vm->global)
			print_arena(vm, step, 32);
		cycle(vm, &op_tab);
		vm->check--;
	}
//	if (vm->color == 1)
//		print_arena_test(vm, step);
	return (1);
}
