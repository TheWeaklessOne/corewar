/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoughnu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 12:19:44 by sdoughnu          #+#    #+#             */
/*   Updated: 2020/02/06 12:19:45 by sdoughnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

t_cur 			*create_cursor(t_cur *old)
{
	t_cur 		*new;
	int 		i;

	if (!(new = (t_cur*)malloc(sizeof(t_cur))))
		exit(1);
	i = -1;
	new->last_cyc_live = old->last_cyc_live;
	new->carry = old->carry;
	new->operation = 0;
	while (++i < REG_NUMBER)
		new->reg[i] = old->reg[i];
	new->id = old->id;
	new->cyc_before_op = 0;
	return (new);
}

void			do_fork(t_vm *vm, t_cur *cur)
{
	t_cur		*new;

	read_args(vm, cur);
	new = create_cursor(cur);
	new->pos = (cur->args[0] % IDX_MOD) % MEM_SIZE;
	new->next = vm->curs;
	vm->curs = new;
}

void			do_lfork(t_vm *vm, t_cur *cur)
{
	t_cur		*new;

	read_args(vm, cur);
	new = create_cursor(cur);
	new->pos = (cur->pos + cur->args[0]) % MEM_SIZE;
	new->next = vm->curs;
	vm->curs = new;
}
