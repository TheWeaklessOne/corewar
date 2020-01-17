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
	return (c);
}

void	push_cur(t_cur *c, t_vm *vm)
{
	t_cur *tmp;

	if (!vm->curs)
		vm->curs = c;
	else
	{
		tmp = vm->curs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = c;
	}
}

int 	cur_init(t_vm *vm)
{
	int		i;
	t_cur	*c;

	i = -1;
	while (++i < vm->players)
	{
		if (!(c = new_cur(i + 1)))
			return (0);
		push_cur(c, vm);
	}
	i = 0;
	printf("Introducing contestants...\n");
	while (++i <= vm->players)
	{
		printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", i,
				vm->champ[i]->size, vm->champ[i]->name, vm->champ[i]->com);
	}
	return (1);
}
