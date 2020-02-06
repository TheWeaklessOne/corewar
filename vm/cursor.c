/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 20:12:32 by wstygg            #+#    #+#             */
/*   Updated: 2020/02/04 20:12:33 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

t_cur			*cur_at(t_cur *cur, int at)
{
	t_cur		*ret;
	int			i;

	if (!cur)
		return (NULL);
	if (at <= 0)
		return (cur);
	ret = cur;
	i = 1;
	while (cur->next && i < at)
	{
		cur = cur->next;
		i++;
	}
	if (i == at)
		return (cur);
	return (ret);
}

t_cur			*cur_remove_at(t_cur *cur, int at)
{
	t_cur		*lst_at;
	t_cur		*lst_before;

	if (!(lst_at = cur_at(cur, at)))
		return (NULL);
	if (lst_at == cur && at != 1)
		return (cur);
	if (at == 1)
	{
		lst_before = cur;
		cur = cur->next;
		free(lst_before);
		lst_before = NULL;
	}
	else
	{
		lst_before = cur_at(cur, at - 1);
		lst_before->next = lst_at->next;
		free(lst_at);
		lst_at = NULL;
	}
	return (cur);
}

void			delete_deads(t_vm *vm)
{
	t_cur		*cur;
	int			at;

	at = 1;
	cur = vm->curs;
	while (cur)
	{
		if (vm->cycles_to_die <= 0 ||
			vm->global - cur->last_cyc_live >= (unsigned)vm->cycles_to_die)
		{
			vm->curs = cur_remove_at(vm->curs, at);
			vm->curs_alive--;
		}
		else
			at++;
		cur = cur->next;
	}
}
