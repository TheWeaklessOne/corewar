/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoye <djoye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 20:19:50 by wstygg            #+#    #+#             */
/*   Updated: 2020/02/18 16:03:03 by djoye            ###   ########.fr       */
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
	if (op.arg_count >= 1)
		if (!(op.arg_type[0] & args_type[0]))
			return (0);
	if (op.arg_count >= 2)
		if (op.arg_type[1] && !(op.arg_type[1] & args_type[1]))
			return (0);
	if (op.arg_count >= 3)
		if (op.arg_type[2] && !(op.arg_type[2] & args_type[2]))
			return (0);
	return (1);
}

int					skip_uncorrect(t_cur *cur, const t_op *op)
{
	int				skip;
	int				i;

	skip = op->code_type_arg ? 2 : 1;
	i = 0;
	while (i < op->arg_count)
	{
		skip += cur->arg_size[i];
		i++;
	}
	return (skip);
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
			return (skip_uncorrect(cur, &op));
		}
		cur->arg_size[0] = 4 - 2 * op.dir_size;
		cur->args_type[0] = T_DIR;
		return (0);
	}
	return (1);
}
