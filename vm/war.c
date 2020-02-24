/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   war.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoye <djoye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 10:48:04 by sdoughnu          #+#    #+#             */
/*   Updated: 2020/02/20 16:00:35 by djoye            ###   ########.fr       */
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
		if (c->cyc_before_op <= 0 && (c->operation = v->arena[c->pos]))
			if (c->operation >= 0x01 && c->operation <= 0x10)
				c->cyc_before_op = g_op_tab[c->operation].need_cycles;
		if (--c->cyc_before_op <= 0)
		{
			reset_cur_args(c);
			if (!(skip = check_op(v, c)))
			{
				do_op(v, c);
				if (!v->zj)
					c->pos = (c->pos +
					skip_uncorrect(c, &g_op_tab[c->operation])) % MEM_SIZE;
				else
					v->zj = 0;
			}
				else c->pos = (c->pos + skip) % MEM_SIZE;
		}
		c = c->next;
	}
}

int					war(t_vm *v, int check_count)
{
	if (v->l == 1)
		ft_printf("It is now cycle %lu\n", v->global);
	do_cycle(v);
	check_count++;
	if (check_count >= v->cycles_to_die)
	{
		v->checks++;
		delete_deads(v);
		if (v->live_count >= NBR_LIVE || v->checks == MAX_CHECKS)
		{
			v->cycles_to_die -= CYCLE_DELTA;
			v->checks = 0;
			if (v->l == 1)
				ft_printf("Cycle to die is now %d\n", v->cycles_to_die);
		}
		check_count = 0;
		v->live_count = 0;
	}
	return (check_count);
}

void				end_visu(t_vm *v, WINDOW *vm_window)
{
	int				key;

	key = 0;
	wattron(vm_window, COLOR_PAIR(2));
	mvwprintw(vm_window, 30, SUB, "Contestant %u:",
			v->last_champ->n);
	wattron(vm_window, COLOR_PAIR(3));
	mvwprintw(vm_window, 31, SUB, "\t\"%s\"",
			v->last_champ->name);
	wattron(vm_window, COLOR_PAIR(1));
	mvwprintw(vm_window, 32, SUB, "\t\thas won!\n");
	wattron(vm_window, COLOR_PAIR(0));
	wrefresh(vm_window);
	while (key != KEY_ESC)
		key = getch();
	endwin();
}

int					war_coming(t_vm *v)
{
	int				check_count;

	WINDOW * vm_window;
	vm_window = NULL;
	if (v->color == 1)
		vm_window = init_visu(vm_window, v);
	else if (v->d == 1 && v->d_count == 0)
		return (print_arena(v, 64) + 1);
	else if (v->dump == 1 && v->dump_count == 0)
		return (print_arena(v, 32) + 1);
	check_count = 0;
	while (++v->global && v->curs_alive > 0)
	{
		if (v->global == 2425)
			printf("");
		check_count = war(v, check_count);
		if (v->d == 1 && v->global == (unsigned long)v->d_count)
			return (print_arena(v, 64) + 1);
		if (v->dump == 1 && v->global == (unsigned long)v->dump_count)
			return (print_arena(v, 32) + 1);
		if (v->color == 1)
			remote(vm_window, v);
	}
	(v->color == 1) ? end_visu(v, vm_window) : 0;
	ft_printf("Contestant %u, \"%s\", has won !\n", v->last_champ->n,
			v->last_champ->name);
	return (1);
}
