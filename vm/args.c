/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoye <djoye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 20:06:04 by wstygg            #+#    #+#             */
/*   Updated: 2020/02/19 16:06:05 by djoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

t_4bits				swap_bits(unsigned char nb)
{
	t_4bits			ret;
	unsigned		save;

	ret.arg = nb;
	save = ret.f.a3;
	ret.f.a3 = ret.f.a0;
	ret.f.a0 = save;
	save = ret.f.a2;
	ret.f.a2 = ret.f.a1;
	ret.f.a1 = save;
	return (ret);
}

int					read_t_dir(t_vm *vm, int pos, int size)
{
	t_4bytes		ret;

	ret.hex = 0;
	if (size == 4)
	{
		ret.f.o4 = vm->arena[pos];
		ret.f.o3 = vm->arena[(pos + 1) % MEM_SIZE];
		ret.f.o2 = vm->arena[(pos + 2) % MEM_SIZE];
		ret.f.o1 = vm->arena[(pos + 3) % MEM_SIZE];
	}
	else
	{
		ret.f.o2 = vm->arena[pos];
		ret.f.o1 = vm->arena[(pos + 1) % MEM_SIZE];
		ret.hex = (int16_t)ret.hex;
	}
	return (ret.hex);
}

int					read_t_ind(t_vm *vm, int pos, int cpos)
{
	t_4bytes		ret;
	//t_4bytes		arg;
	t_2bytes		arg;
	int				skip;
	
	arg.f.o1 = vm->arena[(pos + 1) % MEM_SIZE];
	arg.f.o2 = vm->arena[pos];
// arg.f.o4 = vm->arena[pos];
// 	arg.f.o3 = vm->arena[(pos + 1) % MEM_SIZE];
// 	arg.f.o2 = vm->arena[(pos + 2) % MEM_SIZE];
// 	arg.f.o1 = vm->arena[(pos + 3) % MEM_SIZE];
	skip = (int)arg.hex;
	if (-skip > cpos)
	{
		skip %= IDX_MOD;
		skip += cpos;
		skip %= MEM_SIZE;
		skip = MEM_SIZE + skip;

		ret.f.o4 = vm->arena[(skip) % MEM_SIZE];
		ret.f.o3 = vm->arena[(skip + 1) % MEM_SIZE];
		ret.f.o2 = vm->arena[(skip + 2) % MEM_SIZE];
		ret.f.o1 = vm->arena[(skip + 3) % MEM_SIZE];
	}
	else
	{
		skip %= IDX_MOD;
		ret.f.o4 = vm->arena[(cpos + skip) % MEM_SIZE];
		ret.f.o3 = vm->arena[(cpos + (skip + 1)) % MEM_SIZE];
		ret.f.o2 = vm->arena[(cpos + (skip + 2)) % MEM_SIZE];
		ret.f.o1 = vm->arena[(cpos + (skip + 3)) % MEM_SIZE];
	}
	return (ret.hex);
}

int					get_t_ind(t_vm *vm, int pos)
{
	t_4bytes		arg;

	arg.f.o4 = vm->arena[pos];
	arg.f.o3 = vm->arena[(pos + 1) % MEM_SIZE];
	arg.f.o2 = vm->arena[(pos + 2) % MEM_SIZE];
	arg.f.o1 = vm->arena[(pos + 3) % MEM_SIZE];
	return (arg.hex % IDX_MOD);
}

void				read_args(t_vm *v, t_cur *c)
{
	if (c->args_type[0] == T_REG)
		c->args[0] = v->arena[(c->pos + 2) % MEM_SIZE];
	else if (c->args_type[0] == T_DIR)
		c->args[0] = read_t_dir(v, (c->pos + 2) % MEM_SIZE, c->arg_size[0]);
	else if (c->args_type[0] == T_IND)
		c->args[0] = read_t_ind(v, (c->pos + 2) % MEM_SIZE, c->pos);
	if (c->args_type[1] == T_REG)
		c->args[1] = v->arena[(c->pos + 2 + c->arg_size[0]) % MEM_SIZE];
	else if (c->args_type[1] == T_DIR)
		c->args[1] = read_t_dir(v, (c->pos + 2 + c->arg_size[0]) %
		MEM_SIZE, c->arg_size[1]);
	else if (c->args_type[1] == T_IND)
		c->args[1] = read_t_ind(v, (c->pos + 2 + c->arg_size[0])
			% MEM_SIZE, c->pos);
	if (c->args_type[2] == T_REG)
		c->args[2] = v->arena[(c->pos + 2 + c->arg_size[0] + c->arg_size[1])
			% MEM_SIZE];
	else if (c->args_type[2] == T_DIR)
		c->args[2] = read_t_dir(v, (c->pos + 2 + c->arg_size[0] +
			c->arg_size[1]) % MEM_SIZE, c->arg_size[2]);
	else if (c->args_type[2] == T_IND)
		c->args[2] = read_t_ind(v, (c->pos + 2 + c->arg_size[0] +
			c->arg_size[1]) % MEM_SIZE, c->pos);
}

void				get_arg_types(unsigned char c, unsigned *args)
{
	t_4bits			bits;

	bits = swap_bits(c);
	(bits.f.a0 == REG_CODE) ? args[0] = T_REG : 0;
	(bits.f.a0 == DIR_CODE) ? args[0] = T_DIR : 0;
	(bits.f.a0 == IND_CODE) ? args[0] = T_IND : 0;
	(bits.f.a1 == REG_CODE) ? args[1] = T_REG : 0;
	(bits.f.a1 == DIR_CODE) ? args[1] = T_DIR : 0;
	(bits.f.a1 == IND_CODE) ? args[1] = T_IND : 0;
	(bits.f.a2 == REG_CODE) ? args[2] = T_REG : 0;
	(bits.f.a2 == DIR_CODE) ? args[2] = T_DIR : 0;
	(bits.f.a2 == IND_CODE) ? args[2] = T_IND : 0;
	args[3] = bits.f.a3;
}
