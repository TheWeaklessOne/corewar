/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoye <djoye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 17:15:21 by sdoughnu          #+#    #+#             */
/*   Updated: 2020/02/18 15:25:30 by djoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void				do_st(t_vm *vm, t_cur *cur)
{
	t_4bytes		arg;
	int				skip;

	if (cur->args_type[0] == T_REG)
		cur->args[0] = vm->arena[(cur->pos + 2) % MEM_SIZE];
	if (cur->args_type[1] == T_REG)
	{
		cur->args[1] = vm->arena[(cur->pos + 2 + cur->arg_size[0]) % MEM_SIZE];
		cur->reg[cur->args[1] - 1] = cur->reg[cur->args[0] - 1];
	}
	else if (cur->args_type[1] == T_IND)
	{
		skip = read_t_dir(vm, (cur->pos + 2 + cur->arg_size[0]) % MEM_SIZE,
				cur->arg_size[1]);
		cur->args[1] = skip;
		skip %= IDX_MOD;
		arg.hex = cur->reg[cur->args[0] - 1];
		place_arena_st(skip, cur, arg, vm);
	}
	(vm->l == 1) ? ft_printf("st r%d %d\n", cur->args[0], cur->args[1]) : 0;
}

void				do_add(t_vm *vm, t_cur *cur)
{
	read_args(vm, cur);
	cur->reg[cur->args[2] - 1] =
			cur->reg[cur->args[0] - 1] + cur->reg[cur->args[1] - 1];
	if (cur->reg[cur->args[2] - 1] == 0)
		cur->carry = 1;
	else
		cur->carry = 0;
	if (vm->l == 1)
		ft_printf("add r%d r%d r%d\n", cur->args[0],
				cur->args[1], cur->args[2]);
}

void				do_sub(t_vm *vm, t_cur *cur)
{
	read_args(vm, cur);
	cur->reg[cur->args[2] - 1] =
			cur->reg[cur->args[0] - 1] - cur->reg[cur->args[1] - 1];
	if (cur->reg[cur->args[2] - 1] == 0)
		cur->carry = 1;
	else
		cur->carry = 0;
	(vm->l == 1) ? ft_printf("sub r%d r%d r%d\n", cur->args[0],
			cur->args[1], cur->args[2]) : 0;
}

void				do_and(t_vm *vm, t_cur *cur)
{
	read_args(vm, cur);
	if (cur->args_type[0] == T_REG)
		cur->args[0] = cur->reg[cur->args[0] - 1];
	if (cur->args_type[1] == T_REG)
		cur->args[1] = cur->reg[cur->args[1] - 1];
	cur->reg[cur->args[2] - 1] = cur->args[0] & cur->args[1];
	cur->carry = (cur->reg[cur->args[2] - 1] == 0) ? 1 : 0;
	(vm->l == 1) ? ft_printf("and %d %d r%d\n", cur->args[0],
			cur->args[1], cur->args[2]) : 0;
}

void				do_or(t_vm *vm, t_cur *cur)
{
	read_args(vm, cur);
	if (cur->args_type[0] == T_REG)
		cur->args[0] = cur->reg[cur->args[0] - 1];
	if (cur->args_type[1] == T_REG)
		cur->args[1] = cur->reg[cur->args[1] - 1];
	cur->reg[cur->args[2] - 1] = cur->args[0] | cur->args[1];
	cur->carry = (cur->reg[cur->args[2] - 1] == 0) ? 1 : 0;
	(vm->l == 1) ? ft_printf("or %d %d r%d\n", cur->args[0],
			cur->args[1], cur->args[2]) : 0;
}
