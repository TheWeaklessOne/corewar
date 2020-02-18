/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   war.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoye <djoye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 10:48:04 by sdoughnu          #+#    #+#             */
/*   Updated: 2020/02/18 18:10:02 by djoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void				reset_cur_args(t_cur *cur)
{
	cur->arg_size[0] = 0;
	cur->arg_size[1] = 0;
	cur->arg_size[2] = 0;
	cur->args[0] = 0;
	cur->args[1] = 0;
	cur->args[2] = 0;
	cur->args_type[0] = 0;
	cur->args_type[1] = 0;
	cur->args_type[2] = 0;
	cur->args_type[3] = 0;
}

void				do_cycle(t_vm *v)
{
	t_cur			*c;
	int				skip;

	c = v->curs;
	while (c)
	{
		if (c->cyc_before_op <= 0)
			if ((c->operation = v->arena[c->pos]) >= 0x01
				&& c->operation <= 0x10)
				c->cyc_before_op = g_op_tab[c->operation].need_cycles;
		if (--c->cyc_before_op <= 0)
		{
			reset_cur_args(c);
			if (!(skip = check_op(v, c)))
			{
				do_op(v, c);
				if (!v->zj)
					c->pos = (c->pos + skip_uncorrect(c, &g_op_tab[c->operation])) % MEM_SIZE;
				else
					v->zj = 0;
			}
			else
				c->pos = (c->pos + skip) % MEM_SIZE;
		}
		c = c->next;
	}
}

int					war_coming(t_vm *v)
{
	WINDOW *vm_window = NULL;
	int				check_count;

	check_count = v->cycles_to_die;
	if (v->color == 1)
		vm_window = init_visu(vm_window, v);
	if (v->d == 1 && v->d_count == 0)
		return (print_arena(v, 64) + 1);
	if (v->dump == 1 && v->dump_count == 0)
		return (print_arena(v, 32) + 1);
	check_count = 0;
	while (++v->global)
	{
		if (v->global == 49)
			printf("");
		if (v->l == 1)
			ft_printf("It is now cycle %lu\n", v->global);
		do_cycle(v);
		check_count++;
		if (check_count >= v->cycles_to_die) //v->cycles_to_die <= 0 || 
		{
			v->checks++;
			delete_deads(v);
			if (v->live_count >= NBR_LIVE || v->checks == MAX_CHECKS)
			{
				v->live_count = 0; // перенес сюда
				v->cycles_to_die -= CYCLE_DELTA;
				v->checks = 0;
				(v->l == 1) ? ft_printf("Cycle to die is now %d\n", v->cycles_to_die) : 0;
			}
			check_count = 0;
			v->live_count = 0;
			v->lives_in_cur_period = 0;
		}
		if (v->curs_alive == 0)
			break ;
		if (v->d == 1 && v->global == (unsigned long)v->d_count)
			return (print_arena(v, 64) + 1);
		if (v->dump == 1 && v->global == (unsigned long)v->dump_count)
			return (print_arena(v, 32) + 1);
		if (v->color == 1)
			print_visu(vm_window, v);
	}
	//if (v->color == 1)
	//	endwin();
	if (v->last_champ)
		printf("Contestant %u, \"%s\", has won !\n", v->last_champ->n, v->last_champ->name);
	return (1);
}
