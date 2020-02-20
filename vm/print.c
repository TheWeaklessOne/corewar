/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoye <djoye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 18:24:30 by djoye             #+#    #+#             */
/*   Updated: 2020/02/20 13:33:02 by djoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

WINDOW			*init_visu(WINDOW *vm_window, t_vm *vm)
{
	initscr();
	keypad(stdscr, true);
	nodelay(stdscr, true);
	curs_set(false);
	cbreak();
	noecho();
	start_color();
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(10, COLOR_BLACK, COLOR_WHITE);
	init_pair(11, COLOR_BLACK, COLOR_RED);
	init_pair(12, COLOR_BLACK, COLOR_GREEN);
	init_pair(13, COLOR_BLACK, COLOR_YELLOW);
	init_pair(14, COLOR_BLACK, COLOR_BLUE);
	max_name(vm);
	vm->step = 1;
	vm->speed = 5;
	vm_window = newwin(HEIGHT, vm->width, 0, 0);
	return (vm_window);
}

void			remote(WINDOW *vm_window, t_vm *vm)
{
	int			key;

	key = getch();
	if (key == KEY_ESC)
		exit(endwin());
	else if (vm->step == 1 || key == KEY_STEP || key == ' ' || key == '0')
		pause_step(vm_window, vm);
	else if ((key == KEY_DOWN || key == '-') && vm->speed > 1)
		vm->speed--;
	else if ((key == KEY_UP || key == '+') && vm->speed < 9)
		vm->speed++;
	else if (key >= '1' && key <= '9')
		vm->speed = key - 48;
	print_visu(vm_window, vm, 0);
}

void			print_visu(WINDOW *vm_window, t_vm *vm, int flag)
{
	small_screen(vm_window, vm);
	print_matrix(vm_window, vm);
	print_sub_win(vm, vm_window);
	mvwprintw(vm_window, 58, SUB + 4, "HELP");
	mvwprintw(vm_window, 59, SUB, "speed: '1'-'9'");
	mvwprintw(vm_window, 60, SUB, "speed+: up / '+'");
	mvwprintw(vm_window, 61, SUB, "speed-: down / '-'");
	mvwprintw(vm_window, 62, SUB, "pause: space / '0'");
	mvwprintw(vm_window, 63, SUB, "step: enter");
	mvwprintw(vm_window, 64, SUB, "exit: esc\n");
	wrefresh(vm_window);
	usleep(flag ? 10000 : 500000 / (vm->speed * vm->speed * vm->speed));
}

void			print_matrix(WINDOW *vm_window, t_vm *vm)
{
	int			color;
	int			i;
	t_cur		*tmp;
	int			row;

	i = -1;
	row = 1;
	while (++i < MEM_SIZE)
	{
		if (i % SIZE_64 == 0)
			wmove(vm_window, row++, 2);
		color = vm->map_color[i];
		tmp = vm->curs;
		while (tmp)
			if ((tmp->pos == i) && (color += 10))
				break ;
			else
				tmp = tmp->next;
		wattron(vm_window, COLOR_PAIR(color));
		wprintw(vm_window, "%02x", (unsigned char)vm->arena[i]);
		wattroff(vm_window, COLOR_PAIR(color));
		waddch(vm_window, ' ');
	}
}

void			print_sub_win(t_vm *vm, WINDOW *vm_window)
{
	int			i;

	i = 0;
	while (++i <= vm->players)
	{
		wattron(vm_window, COLOR_PAIR(i));
		mvwprintw(vm_window, i, SUB, "player %d: %s", i,
		vm->champ[i - 1]->name);
		if (vm->last_champ == vm->champ[i - 1])
			mvwprintw(vm_window, 12 + vm->players, SUB, "Last live:%s\n",
			vm->last_champ->name);
		wattroff(vm_window, COLOR_PAIR(i));
	}
	wattron(vm_window, COLOR_PAIR(vm->step == 0 ? 2 : 1));
	mvwprintw(vm_window, ++i, SUB,
	vm->step == 0 ? "********RUN********\n" : "*******PAUSE*******\n");
	wattroff(vm_window, COLOR_PAIR(vm->step == 0 ? 2 : 1));
	mvwprintw(vm_window, ++i, SUB, "Speed: %12d\n", vm->speed);
	mvwprintw(vm_window, i += 2, SUB, "Cycle: %12d", vm->global);
	mvwprintw(vm_window, ++i, SUB, "Cursors: %10u", vm->curs_alive);
	mvwprintw(vm_window, ++i, SUB, "Cycle to die: %5d", vm->cycles_to_die);
	mvwprintw(vm_window, ++i, SUB, "Cycle delta: %6d", CYCLE_DELTA);
	mvwprintw(vm_window, ++i, SUB, "Lives: %9d/%2d", vm->live_count, NBR_LIVE);
	mvwprintw(vm_window, ++i, SUB, "Checks: %8d/%2d", vm->checks, MAX_CHECKS);
}
