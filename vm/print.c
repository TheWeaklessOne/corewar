/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoye <djoye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 18:24:30 by djoye             #+#    #+#             */
/*   Updated: 2020/02/10 17:58:55 by djoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

void			print_sub_win(t_vm *vm, WINDOW *vm_window)
{
	int			i;

	i = 0;
	while (++i <= vm->players)
	{
		wattron(vm_window, COLOR_PAIR(i));
		mvwprintw(vm_window, i, COMMENT, "player %d: %s", i,
		vm->champ[i - 1]->name);
		wattroff(vm_window, COLOR_PAIR(i));
	}
	mvwprintw(vm_window, ++i + 1, COMMENT, "Cycle: %11d", vm->global);
	mvwprintw(vm_window, ++i + 1, COMMENT, "Cursors: %9u", vm->curs_alive);
	mvwprintw(vm_window, ++i + 1, COMMENT, "Cycle to die: %4d", vm->cycles_to_die);
	mvwprintw(vm_window, ++i + 1, COMMENT, "Cycle delta: %5d", CYCLE_DELTA);
	mvwprintw(vm_window, ++i + 1, COMMENT, "Lives: %8d/%2d", vm->live_count,
	NBR_LIVE);
	mvwprintw(vm_window, ++i + 1, COMMENT, "Checks: %7d/%2d", vm->checks,
	MAX_CHECKS);
	if (vm->last_champ)
	{
		wattron(vm_window, COLOR_PAIR((int)vm->last_champ->n));
		mvwprintw(vm_window, ++i + 2, COMMENT, "Last live:%s\n", vm->last_champ->name);
		wattroff(vm_window, COLOR_PAIR((int)vm->last_champ->n));
	}
}

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
	vm_window = newwin(HEIGHT, vm->width, 0, 0);
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

void			small_screen(WINDOW *vm_window, t_vm *vm)
{
	struct winsize	w;
	
	ioctl(0, TIOCGWINSZ, &w);
	if (w.ws_col < vm->width || w.ws_row < HEIGHT)
	{
		delwin(vm_window);
		endwin();
		printf("USAGE: small window for work with flag -v: ");
		if (w.ws_col < getmaxx(vm_window))
			printf("needs %d columns\n", vm->width - w.ws_col);
		if (w.ws_row < getmaxy(vm_window))
			printf("needs %d rows\n", HEIGHT - w.ws_row);
		exit (0);
	}
}

void			print_visu(WINDOW *vm_window, t_vm *vm)
{
	int			key;

	key = getch();
	if (key == KEY_DOWN)
		vm->speed < 600000.0 ? vm->speed *= 2 : 0;
	else if (key == KEY_UP)
		vm->speed > 60.0 ? vm->speed /= 2 : 0;
	else if (key == KEY_ESC)
		exit (endwin());
	else if (key == KEY_SPACE)
		while ((key = getch()))
		{
			if (key == KEY_SPACE)
				break ;
			else if (key == KEY_ESC)
				exit (endwin());
		}
	small_screen(vm_window, vm);
	print_matrix(vm_window, vm);
	print_sub_win(vm, vm_window);
	wrefresh(vm_window);
	usleep(vm->speed);
}

void			max_name(t_vm *vm)
{
	int			i;

	vm->len_name = 0;
	i = 0;
	while (i < vm->players)
	{
		if (ft_strlen(vm->champ[i]->name) > vm->len_name)
			vm->len_name = ft_strlen(vm->champ[i]->name);
		i++;
	}
	vm->width = WIDTH + (vm->len_name > 20 ? vm->len_name - 7 : 0);
}