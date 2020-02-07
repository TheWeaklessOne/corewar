/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 20:11:34 by wstygg            #+#    #+#             */
/*   Updated: 2020/02/04 20:11:35 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void				do_xor(t_vm *vm, t_cur *cur)
{
	read_args(vm, cur);
	cur->reg[cur->args[2]] = cur->args[0] ^ cur->args[1];
	cur->carry = cur->reg[cur->args[2]] == 0;
}

void				do_sti(t_vm *vm, t_cur *cur)
{
	read_args(vm, cur);
	vm->arena[(cur->pos + (cur->args[1] + cur->args[2]) % IDX_MOD) % MEM_SIZE] =
			cur->reg[cur->args[0]];
}

void				do_live(t_vm *vm, t_cur *cur)
{
	int				arg;

	cur->last_cyc_live = vm->global;
	vm->live_count++;
	arg = -read_t_dir(vm, cur->pos + 1, cur->arg_size[0]);
	if (arg >= 1 && arg <= vm->players)
		vm->last_champ = vm->champ[arg - 1];
}

void				do_ld(t_vm *vm, t_cur *cur)
{
	read_args(vm, cur);
	if (cur->args[0] == 0)
		cur->carry = 1;
	else
		cur->carry = 0;
	cur->reg[cur->args[1]] = cur->args[0];
}

void				do_zjmp(t_vm *vm, t_cur *cur)
{
	int				dir;

	dir = read_t_dir(vm, ((cur->pos + 1) % MEM_SIZE), cur->arg_size[0]);
	if (cur->carry)
		cur->pos = (cur->pos + dir % IDX_MOD) % MEM_SIZE;
}
