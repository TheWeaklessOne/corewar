/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 20:19:50 by wstygg            #+#    #+#             */
/*   Updated: 2020/02/04 20:19:51 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void				calc_arg_size(unsigned *args_t, int *arg_size, int size)
{
	(args_t[0] == T_IND) ? arg_size[0] = IND_SIZE : 0;
	(args_t[0] == T_REG) ? arg_size[0] = 1 : 0;
	(args_t[0] == T_DIR) ? arg_size[0] = (4 - 2 * size) : 0;
	(args_t[1] == T_IND) ? arg_size[1] = IND_SIZE : 0;
	(args_t[1] == T_REG) ? arg_size[1] = 1 : 0;
	(args_t[1] == T_DIR) ? arg_size[1] = (4 - 2 * size) : 0;
	(args_t[2] == T_IND) ? arg_size[2] = IND_SIZE : 0;
	(args_t[2] == T_REG) ? arg_size[2] = 1 : 0;
	(args_t[2] == T_DIR) ? arg_size[2] = (4 - 2 * size) : 0;
}

int					check_t_reg(t_vm *vm, t_cur *cur, unsigned *args_t)
{
	int				reg;

	if (args_t[0] == T_REG)
	{
		reg = vm->arena[(cur->pos + 2) % MEM_SIZE];
		if (reg <= 0 || reg > REG_NUMBER)
			return (0);
	}
	if (args_t[1] == T_REG)
	{
		reg = vm->arena[(cur->pos + 2 + cur->arg_size[0]) % MEM_SIZE];
		if (reg <= 0 || reg > REG_NUMBER)
			return (0);
	}
	if (args_t[2] == T_REG)
	{
		reg = vm->arena[(cur->pos + 2 + cur->arg_size[0] +
			cur->arg_size[1]) % MEM_SIZE];
		if (reg <= 0 || reg > REG_NUMBER)
			return (0);
	}
	return (1);
}

int					check_types(unsigned *args_type, t_op op)
{
	if (!(op.arg_type[0] & args_type[0]))
		return (0);
	if (op.arg_type[1] && !(op.arg_type[1] & args_type[1]))
		return (0);
	if (op.arg_type[2] && !(op.arg_type[2] & args_type[2]))
		return (0);
	if (args_type[3])
		return (0);
	return (1);
}

int					check_op(t_vm *vm, t_cur *cur)
{
	t_op			op;

	if (cur->operation >= 0x01 && cur->operation <= 0x10)
	{
		op = g_op_tab[cur->operation];
		if (op.code_type_arg)
		{
			get_arg_types(vm->arena[(cur->pos + 1) % MEM_SIZE], cur->args_type);
			calc_arg_size(cur->args_type, cur->arg_size, op.dir_size);
			if (check_types(cur->args_type, op))
				if (check_t_reg(vm, cur, cur->args_type))
					return (0);
			return (2 + cur->arg_size[0] + cur->arg_size[1] + cur->arg_size[2]);
		}
		cur->arg_size[0] = 4 - 2 * op.dir_size;
		cur->args_type[0] = T_DIR;
		return (0);
	}
	return (1);
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
