/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cur.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoughnu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 14:05:44 by sdoughnu          #+#    #+#             */
/*   Updated: 2020/01/17 14:05:45 by sdoughnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

t_cur	*new_cur(int i)
{
	t_cur	*c;

	if (!(c = (t_cur*)malloc(sizeof(t_cur))))
		return (NULL);
	c->id = i;
	c->last_cyc_live = 0;
	c->cyc_before_op = 0;
	c->carry = 0;
	c->id_player = i;
	ft_bzero(c->reg, sizeof(int) * 16);
	c->next = NULL;
	return (c);
}

void	push_cur(t_cur *c, t_vm *vm)
{
	if (!vm->curs)
		vm->curs = c;
	else
	{
		c->next = vm->curs;
		vm->curs = c;
	}
}

int 	cur_init(t_vm *vm)
{
	int		i;
	t_cur	*c;
	int 	step;
	int 	start;

	i = -1;
	start = 0;
	step = MEM_SIZE / vm->players;
	while (++i < vm->players)
	{
		if (!(c = new_cur(i + 1)))
			return (printf("Memory not allocated\n") - 21);
		c->pos = start;
		push_cur(c, vm);
		start += step;
	}
	i = -1;
	printf("Introducing contestants...\n");
	while (++i < vm->players)
	{
		printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", i,
				vm->champ[i]->size, vm->champ[i]->name, vm->champ[i]->com);
	}
	return (1);
}
