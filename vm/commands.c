/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoye <djoye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 20:11:34 by wstygg            #+#    #+#             */
/*   Updated: 2020/02/17 17:38:08 by djoye            ###   ########.fr       */
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

void                place_to_arena(t_vm *vm, int place, int pos, int skip, t_cur *cur)
{
    t_4bytes        arg;

    arg.hex = place;
    vm->arena[(pos + skip) % MEM_SIZE] = arg.f.o4;
    vm->arena[(pos + (skip + 1) % IDX_MOD) % MEM_SIZE] = arg.f.o3;
    vm->arena[(pos + (skip + 2) % IDX_MOD) % MEM_SIZE] = arg.f.o2;
    vm->arena[(pos + (skip + 3) % IDX_MOD) % MEM_SIZE] = arg.f.o1;
	vm->map_color[(pos + skip) % MEM_SIZE] = cur->id;
    vm->map_color[(pos + (skip + 1) % IDX_MOD) % MEM_SIZE] = cur->id;
    vm->map_color[(pos + (skip + 2) % IDX_MOD) % MEM_SIZE] = cur->id;
    vm->map_color[(pos + (skip + 3) % IDX_MOD) % MEM_SIZE] = cur->id;
}

void				do_sti(t_vm *vm, t_cur *cur)
{
    t_4bytes        arg;
    int             skip;

	read_args(vm, cur);
	if (cur->args_type[1] == T_REG)
		cur->args[1] = cur->reg[cur->args[1] - 1];
	if (cur->args_type[2] == T_REG)
		cur->args[2] = cur->reg[cur->args[2] - 1];
	arg.hex = cur->reg[cur->args[0] - 1];
	skip = (cur->args[1] + cur->args[2]) % IDX_MOD;
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
		place_to_arena(vm, arg.hex, cur->pos, skip, cur);
	if (vm->l == 1)
	{
		ft_printf("sti r%d %d %d\n", cur->args[0], cur->args[1], cur->args[2]);
		ft_printf("       | -> store to %d + %d = %d ", cur->args[1], cur->args[2],
				(cur->args[1] + cur->args[2]));
		ft_printf("(with pc and mod %d)\n",
				(cur->pos + (cur->args[1] + cur->args[2]) % IDX_MOD));
	}
}

void				do_live(t_vm *vm, t_cur *cur)
{
	int				arg;

	arg = -read_t_dir(vm, (cur->pos + 1) % MEM_SIZE, cur->arg_size[0]);
	if (vm->l == 1)
		ft_printf("live %d\n", (-arg));
	cur->last_cyc_live = vm->global;
	if (arg >= 1 && arg <= vm->players)
	{
		vm->live_count++;
		vm->last_champ = vm->champ[arg - 1];
	}
		
}

void				do_ld(t_vm *vm, t_cur *cur)
{
	read_args(vm, cur);
	if (cur->args[0] == 0)
		cur->carry = 1;
	else
		cur->carry = 0;
	cur->reg[cur->args[1] - 1] = cur->args[0];
	(vm->l == 1) ? ft_printf("ld %d r%d\n", cur->args[0], cur->args[1]) : 0;
}

void				do_zjmp(t_vm *vm, t_cur *cur)
{
	int				dir;

	dir = read_t_dir(vm, ((cur->pos + 1) % MEM_SIZE), cur->arg_size[0]);
	if (vm->l == 1)
		ft_printf("zjmp %d %s", dir, cur->carry ? "OK\n" : "FAILED\n");
	dir %= IDX_MOD;
	if (cur->carry)
	{
		if (-dir > cur->pos)
		{
			dir += cur->pos;
			dir %= MEM_SIZE;
			(cur->carry) ? cur->pos = MEM_SIZE + dir : 0;
		}
		else
			cur->pos = (cur->pos + dir) % MEM_SIZE;
		vm->zj = 1;
	}
}
