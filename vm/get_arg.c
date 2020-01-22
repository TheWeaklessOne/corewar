/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoye <djoye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:29:10 by djoye             #+#    #+#             */
/*   Updated: 2020/01/22 12:39:51 by djoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"
#include "../includes/op.h"

/*
int     get_arg(t_vm *vm, t_cur *cur, unsigned char arg, int mod)
{
    int value;
    int address;
    t_op *op;

    value = 0;
    //op = &op_tab[cur->operation];
    if (arg == T_DIR)
    {
      //  value = get_map_dir(vm->arena, cur->pos + cur->step, op->dir_size);
        cur->step += op->dir_size;
    }
    else if (arg == T_REG)
        return (value); 
}
*/
int     check_arg(char arg)
{
    if (arg & T_IND)
        return (T_IND);
    else if (arg & T_DIR)
        return (T_DIR);
    else if (arg & T_REG)
        return (T_REG);
    return (0);
}

int     bit(unsigned char byte, char arg_num)
{
    t_4bits num;
    char    check;

    num.arg = byte;
    if (arg_num == 1)
        check = check_arg(num.field.arg_1);
    else if (arg_num == 2)
        check = check_arg(num.field.arg_2);
    else if (arg_num == 3)
        check = check_arg(num.field.arg_3);
    else if (arg_num == 4)
        check = check_arg(num.field.arg_4);
    printf ("-%d-\n", check);
    return (check);
}