/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoye <djoye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:29:10 by djoye             #+#    #+#             */
/*   Updated: 2020/01/21 18:19:16 by djoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"
#include "../includes/op.h"

int     get_arg(t_vm *vm, t_cur *cur, unsigned char arg, int mod)
{
    int value;
    int address;
    t_op *op;

    value = 0;
    op = &op_tab[cur->operation];
    if (arg == T_DIR)
    {
        value = get_map_dir(vm->arena, cur->pos + cur->step, op->dir_size);
        cur->step += op->dir_size;
    }
    else if (arg == T_REG)
    {
        address = get_map_ind(cur->)

    }

    
}