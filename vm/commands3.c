/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoughnu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 11:24:38 by sdoughnu          #+#    #+#             */
/*   Updated: 2020/02/20 11:24:39 by sdoughnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void				do_xor(t_vm *vm, t_cur *cur)
{
	read_args(vm, cur);
	if (cur->args_type[0] == T_REG)
		cur->args[0] = cur->reg[cur->args[0] - 1];
	if (cur->args_type[1] == T_REG)
		cur->args[1] = cur->reg[cur->args[1] - 1];
	cur->reg[cur->args[2] - 1] = cur->args[0] ^ cur->args[1];
	cur->carry = (cur->reg[cur->args[2] - 1]) == 0 ? 1 : 0;
	(vm->l == 1) ? ft_printf("xor %d %d r%d\n", cur->args[0],
			cur->args[1], cur->args[2]) : 0;
}

void				l_for_sti(t_vm *vm, t_cur *cur)
{
	if (vm->l == 1)
	{
		ft_printf("sti r%d %d %d\n", cur->args[0], cur->args[1], cur->args[2]);
		ft_printf("       | -> store to %d + %d = %d ", cur->args[1],
				cur->args[2], (cur->args[1] + cur->args[2]));
		ft_printf("(with pc and mod %d)\n",
				(cur->pos + (cur->args[1] + cur->args[2]) % IDX_MOD));
	}
}

void				color_map_sti(t_vm *vm, int skip, t_cur *cur)
{
	vm->map_color[skip] = cur->id;
	vm->map_color[(skip + 1) % MEM_SIZE] = cur->id;
	vm->map_color[(skip + 2) % MEM_SIZE] = cur->id;
	vm->map_color[(skip + 3) % MEM_SIZE] = cur->id;
}

void				place_arena_st(int skip, t_cur *cur, t_4bytes arg, t_vm *vm)
{
	if (-skip > cur->pos)
	{
		skip += cur->pos;
		skip %= MEM_SIZE;
		skip = MEM_SIZE + skip;
		vm->arena[skip] = arg.f.o4;
		vm->arena[(skip + 1) % MEM_SIZE] = arg.f.o3;
		vm->arena[(skip + 2) % MEM_SIZE] = arg.f.o2;
		vm->arena[(skip + 3) % MEM_SIZE] = arg.f.o1;
		vm->map_color[skip] = cur->id;
		vm->map_color[(skip + 1) % MEM_SIZE] = cur->id;
		vm->map_color[(skip + 2) % MEM_SIZE] = cur->id;
		vm->map_color[(skip + 3) % MEM_SIZE] = cur->id;
	}
	else
	{
		vm->arena[(cur->pos + skip) % MEM_SIZE] = arg.f.o4;
		vm->arena[(cur->pos + (skip + 1)) % MEM_SIZE] = arg.f.o3;
		vm->arena[(cur->pos + (skip + 2)) % MEM_SIZE] = arg.f.o2;
		vm->arena[(cur->pos + (skip + 3)) % MEM_SIZE] = arg.f.o1;
		vm->map_color[(cur->pos + skip) % MEM_SIZE] = cur->id;
		vm->map_color[(cur->pos + (skip + 1)) % MEM_SIZE] = cur->id;
		vm->map_color[(cur->pos + (skip + 2)) % MEM_SIZE] = cur->id;
		vm->map_color[(cur->pos + (skip + 3)) % MEM_SIZE] = cur->id;
	}
}

void				do_op(t_vm *vm, t_cur *cur)
{
	if (vm->l == 1)
		ft_printf("P %4d | ", cur->p);
	(cur->operation == 1) ? do_live(vm, cur) : 0;
	(cur->operation == 2) ? do_ld(vm, cur) : 0;
	(cur->operation == 3) ? do_st(vm, cur) : 0;
	(cur->operation == 4) ? do_add(vm, cur) : 0;
	(cur->operation == 5) ? do_sub(vm, cur) : 0;
	(cur->operation == 6) ? do_and(vm, cur) : 0;
	(cur->operation == 7) ? do_or(vm, cur) : 0;
	(cur->operation == 8) ? do_xor(vm, cur) : 0;
	(cur->operation == 9) ? do_zjmp(vm, cur) : 0;
	(cur->operation == 10) ? do_ldi(vm, cur) : 0;
	(cur->operation == 11) ? do_sti(vm, cur) : 0;
	(cur->operation == 12) ? do_fork(vm, cur) : 0;
	(cur->operation == 13) ? do_lld(vm, cur) : 0;
	(cur->operation == 14) ? do_lldi(vm, cur) : 0;
	(cur->operation == 15) ? do_lfork(vm, cur) : 0;
	(cur->operation == 16) ? do_aff(vm, cur) : 0;
}
