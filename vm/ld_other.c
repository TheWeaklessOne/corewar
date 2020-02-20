/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld_other.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoye <djoye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 12:18:35 by sdoughnu          #+#    #+#             */
/*   Updated: 2020/02/18 18:20:39 by djoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <zconf.h>
#include "../includes/vm.h"

void			do_ldi(t_vm *vm, t_cur *cur)
{
	int			addr;

	read_args(vm, cur);
	if (cur->args_type[0] == T_REG)
		cur->args[0] = cur->reg[cur->args[0] - 1];
	if (cur->args_type[1] == T_REG)
		cur->args[1] = cur->reg[cur->args[1] - 1];
	addr = (cur->pos + (cur->args[0] + cur->args[1]) % IDX_MOD) % MEM_SIZE;
	cur->reg[cur->args[2] - 1] = read_t_dir(vm, addr, 4);
	(vm->l == 1) ? ft_printf("ldi %d %d r%d\n", cur->args[0],
			cur->args[1], cur->args[2]) : 0;
	(vm->l == 1) ? ft_printf("       | -> load from ") : 0;
	(vm->l == 1) ? ft_printf("%d + %d = %d (with pc and mod %d)\n",
			cur->args[0], cur->args[1], (cur->args[0] + cur->args[1]),
			((cur->pos + (cur->args[0] + cur->args[1]) % IDX_MOD))) : 0;
}

void			do_lld(t_vm *vm, t_cur *cur)
{
	t_4bytes		ret;
	t_4bytes		arg;
	int				pos;
	int				skip;

	if (cur->args_type[0] == T_DIR)
		cur->args[0] = read_t_dir(vm,
				(cur->pos + 2) % MEM_SIZE, cur->arg_size[0]);
	else if (cur->args_type[0] == T_IND)
	{
		pos = (cur->pos + 2) % MEM_SIZE;
		arg.f.o4 = vm->arena[pos];
		arg.f.o3 = vm->arena[(pos + 1) % MEM_SIZE];
		arg.f.o2 = vm->arena[(pos + 2) % MEM_SIZE];
		arg.f.o1 = vm->arena[(pos + 3) % MEM_SIZE];
		skip = arg.hex;
		ret.f.o4 = vm->arena[(cur->pos + skip) % MEM_SIZE];
		ret.f.o3 = vm->arena[(cur->pos + (skip + 1)) % MEM_SIZE];
		ret.f.o2 = vm->arena[(cur->pos + (skip + 2)) % MEM_SIZE];
		ret.f.o1 = vm->arena[(cur->pos + (skip + 3)) % MEM_SIZE];
		cur->args[0] = ret.hex;
	}
	cur->args[1] = vm->arena[(cur->pos + 2 + cur->arg_size[0]) % MEM_SIZE];
	cur->reg[cur->args[1] - 1] = cur->args[0];
	(vm->l == 1) ? ft_printf("lld %d r%d\n", cur->args[0], cur->args[1]) : 0;
}

void			do_lldi(t_vm *vm, t_cur *cur)
{
	int			addr;

	read_args(vm, cur);
	if (cur->args_type[0] == T_REG)
		cur->args[0] = cur->reg[cur->args[0] - 1];
	if (cur->args_type[1] == T_REG)
		cur->args[1] = cur->reg[cur->args[1] - 1];
	addr = (cur->pos + (cur->args[0] + cur->args[1])) % MEM_SIZE;
	cur->reg[cur->args[2] - 1] = read_t_dir(vm, addr, 4);
	(vm->l == 1) ? ft_printf("lldi %d %d r%d\n", cur->args[0],
			cur->args[1], cur->args[2]) : 0;
	(vm->l == 1) ? ft_printf("       | -> load from ") : 0;
	(vm->l == 1) ? ft_printf("%d + %d = %d (with pc %d)\n",
			cur->args[0], cur->args[1], (cur->args[0] + cur->args[1]),
			(cur->pos + (cur->args[0] + cur->args[1]))) : 0;
}

void			do_aff(t_vm *vm, t_cur *cur)
{
	char		c;

	read_args(vm, cur);
	c = (char)cur->args[0];
	write(1, &c, 1);
}
