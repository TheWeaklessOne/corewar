/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cur.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoye <djoye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 14:05:44 by sdoughnu          #+#    #+#             */
/*   Updated: 2020/01/24 17:58:19 by djoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

t_cur			*new_cur(int i)
{
	t_cur		*c;

	if (!(c = (t_cur*)malloc(sizeof(t_cur))))
		return (NULL);
	ft_bzero(c, sizeof(t_cur));
	c->id = i;
	c->reg[0] = -i;
	c->next = NULL;
	return (c);
}

void			push_cur(t_cur *c, t_vm *vm)
{
	if (!vm->curs)
		vm->curs = c;
	else
	{
		c->next = vm->curs;
		vm->curs = c;
	}
}

void			replace_n(t_vm *vm)
{
	int			i;

	i = -1;
	while (++i < vm->players)
		vm->champ[i]->n = i + 1;
}

void			id_cur_flag_l(t_cur *c)
{
	static int	x = 1;

	c->p = x;
	x++;
}

int				cur_init(t_vm *vm)
{
	int			i;
	t_cur		*c;
	const int	step = MEM_SIZE / vm->players;
	int			start;

	i = -1;
	start = 0;
	while (++i < vm->players)
	{
		if (!(c = new_cur(i + 1)))
			return (print_fd("Memory not allocated\n", 2));
		c->pos = start;
		id_cur_flag_l(c);
		push_cur(c, vm);
		start += step;
	}
	i = -1;
	ft_printf("Introducing contestants...\n");
	while (++i < vm->players)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", i + 1,
				vm->champ[i]->size, vm->champ[i]->name, vm->champ[i]->com);
	}
	replace_n(vm);
	return (1);
}
