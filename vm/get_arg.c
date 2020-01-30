/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoye <djoye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:29:10 by djoye             #+#    #+#             */
/*   Updated: 2020/01/29 13:32:57 by djoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

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
    if (c == REG_CODE)
        return (T_REG);
    else if (c == DIR_CODE) 
        return (T_DIR);
    else if (c == IND_CODE)
        return (T_IND);
    else
        return (0);
}

int     check_arg(t_op *op_tab, unsigned char id_op, unsigned char arg)
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
    return (1);
}

int     get_value(t_vm *vm, unsigned char id_op, t_cur *cur, unsigned char arg, t_op *op_tab)
{
    int value;
    int address;

    value = 0;
    if (arg == T_REG)
    {
        address = (cur->pos + cur->step) % MEM_SIZE; ///  
        if (address > 0 && address <= REG_SIZE)
            value = cur->reg[address - 1]; // -1 ???
        cur->step++;
    }
    else if (arg == T_DIR)
    {
        if (op_tab[id_op - 1].dir_size == 4)
            value = swap_int((int*)(vm->arena + cur->pos));
        else
            value = swap_short((short*)(vm->arena + cur->pos));
        cur->step += op_tab[id_op - 1].dir_size;
    }
    else if (arg + 1 == T_IND)
    {
        address = (cur->pos + cur->step) % MEM_SIZE;
        value = swap_int((int*)(vm->arena + cur->pos));
        cur->step += 2;
    }
    return(value);
}

int		swap_int(int *nb)
{
	t_4bytes		num;
	unsigned char	tmp;

	num.hex = *nb;
	tmp = num.field.octet1;
	num.field.octet1 = num.field.octet4;
	num.field.octet4 = tmp;
	tmp = num.field.octet2;
	num.field.octet2 = num.field.octet3;
	num.field.octet3 = tmp;
	return (num.hex);
}

int		swap_short(short *nb)
{
	t_4bytes		num;
	unsigned char	tmp;

	num.hex = *nb;
	tmp = num.field.octet1;
    num.field.octet1 = num.field.octet2;
    num.field.octet2 = tmp;
	return (num.hex);
}