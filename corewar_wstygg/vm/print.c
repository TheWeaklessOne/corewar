/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoye <djoye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 18:24:30 by djoye             #+#    #+#             */
/*   Updated: 2020/02/06 15:20:44 by djoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void			print_sub_win(t_vm *vm, WINDOW *vm_window)
{
	int			i;

	i = -1;
	while (++i < vm->players)
	{
		wattron(vm_window, COLOR_PAIR(i + 1));
		mvwprintw(vm_window, i + 1, COMMENT, "player %d : %s", i + 1,
		vm->champ[i]->name);
		wattroff(vm_window, COLOR_PAIR(i + 1));
	}
	mvwprintw(vm_window, ++i + 1, COMMENT, "Cycles/second : %d", 1000 / 100);
	mvwprintw(vm_window, ++i + 1, COMMENT, "Cycle : %d", vm->global);
	mvwprintw(vm_window, ++i + 1, COMMENT, "Cursors : %d", vm->curs);
	mvwprintw(vm_window, ++i + 1, COMMENT, "players = %d", vm->players);
	mvwprintw(vm_window, ++i + 1, COMMENT, "champs = %d", vm->champ[0]);
	mvwprintw(vm_window, ++i + 1, COMMENT, "Cycle to die : %d", CYCLE_TO_DIE);
	mvwprintw(vm_window, ++i + 1, COMMENT, "Cycle delta : %d", CYCLE_DELTA);
	mvwprintw(vm_window, ++i + 1, COMMENT, "Lives : %d/%d", vm->champ,
	NBR_LIVE);
	mvwprintw(vm_window, ++i + 1, COMMENT, "Cycles to check : %d", vm->champ);
	mvwprintw(vm_window, ++i + 1, COMMENT, "Checks : %d/%d", vm->champ[1],
	MAX_CHECKS);
}

WINDOW			*init_visu(WINDOW *vm_window)
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
	vm_window = newwin(HEIGHT, WIDTH, 0, 0);
	return (vm_window);
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

void			print_visu(WINDOW *vm_window, t_vm *vm)
{
	static int	speed = 10000;
	int			key;

	key = getch();
	if (key == KEY_DOWN)
		speed < 200000 ? speed *= 2 : 0;
	else if (key == KEY_UP)
		speed > 100 ? speed /= 2 : 0;
	else if (key == KEY_SPACE)
		while ((key = getch()))
			if (key == KEY_SPACE)
				break ;
	print_matrix(vm_window, vm);
	print_sub_win(vm, vm_window);
	wrefresh(vm_window);
	usleep(speed);
}
