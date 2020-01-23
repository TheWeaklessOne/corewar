/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoye <djoye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:29:10 by djoye             #+#    #+#             */
/*   Updated: 2020/01/23 16:26:39 by djoye            ###   ########.fr       */
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
int     check_arg_l(char arg)
{
   /* if (arg & T_IND)
        return (T_IND);
    else if (arg & T_DIR)
        return (T_DIR);
    else if (arg & T_REG)
        return (T_REG);
        */
    return (arg & 3);
}
/*
int     check_arg(unsigned char nbr, char arg, char arg_num)
{
    t_4bits num;
    char    check;

    nbr = 11;
    arg_num = 0;
    while (++arg_num <= 4)
{
    num.arg = nbr;
    if (arg_num == 1)
        check = (num.field.arg_1);
    else if (arg_num == 2)
        check = (num.field.arg_2);
    else if (arg_num == 3)
        check = (num.field.arg_3);
    else if (arg_num == 4)
        check = (num.field.arg_4);
        printf ("%d\n", check);
}
    return (check); // & arg);
}
*/

unsigned char swap(unsigned char c)
{
    if (c == 1)
        return (1);
    else if (c == 2) 
        return (2);
    else if (c == 3)
        return (4);
    else
        return (0);
}

int     check_arg(t_op *op_tab, unsigned char id_op, unsigned char arg) //, char arg_num)
{
    t_4bits         num;
    int             i;

    i = 0;
    num.arg = arg;
    while (i < op_tab[id_op - 1].arg_count)
    {
        if (i == 0)
        {
            arg = swap(num.field.arg_1);
            if (!arg || !(arg & op_tab[id_op - 1].arg_type[i]))
                return (0);
        }
        else if (i == 1)
        {
            arg = swap(num.field.arg_2);
            if (!arg || !(arg & op_tab[id_op - 1].arg_type[i]))
                return (0);
        }
        else if (i == 2)
        {
            arg = swap(num.field.arg_3);
            if (!arg || !(arg & op_tab[id_op - 1].arg_type[i]))
                return (0);
        }
        i++;
    }
    return (1); // & arg);
}