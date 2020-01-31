/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoye <djoye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 18:24:30 by djoye             #+#    #+#             */
/*   Updated: 2020/01/31 13:23:56 by djoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"
#include <ncurses.h>
#define SIZE_32				32
#define SIZE_64				64
# define HEIGHT (MEM_SIZE / SIZE_64 + 4)
# define WIDTH	(SIZE_64 * 3 + 100)

void	print_arena_test(t_vm *vm, int step)
{
    WINDOW      *vm_window;
    int         i;
    static int  speed = 10000;
    int         key;
	int			row;
	int			color;
	int			cycle;
	t_cur		*tmp;
	
    initscr(); // перемещение курсора в стандартном экране y=10 x=30
	keypad(stdscr, true);
	nodelay(stdscr, true);
	curs_set(false);
	cbreak();
	noecho();
    vm_window = newwin(HEIGHT, WIDTH, 0, 0);
	cycle = 0;
    while (cycle++ < CYCLE_TO_DIE)
    {
		i = -1;
        key = getch(); // ждём нажатия символа
        if (key == KEY_DOWN)
    	    speed < 200000 ? speed *= 2 : 0;
        else if (key == KEY_UP)
    	   speed > 100 ? speed /= 2 : 0;
		else if(key == 32) // пауза
				while((key = getch()))
					if(key == 32)
						break ;
		row = 1;
		start_color();
		init_pair(0, COLOR_WHITE, COLOR_BLACK);
		init_pair(1, COLOR_RED, COLOR_BLACK);
		init_pair(2, COLOR_GREEN, COLOR_BLACK);
		init_pair(3, COLOR_YELLOW, COLOR_BLACK);
		init_pair(4, COLOR_BLUE, COLOR_BLACK);
		
		init_pair(10, COLOR_BLACK, COLOR_WHITE); // инверсия цвета
		init_pair(11, COLOR_BLACK,COLOR_RED);
		init_pair(12, COLOR_BLACK,COLOR_GREEN);
		init_pair(13, COLOR_BLACK,COLOR_YELLOW);
		init_pair(14, COLOR_BLACK, COLOR_BLUE);

		while(++i < MEM_SIZE)
        {
			if (i % SIZE_64 == 0)
				wmove(vm_window, row++, 2);
			tmp = vm->curs;
			color = vm->map_color[i];
			while(tmp)
				if ((tmp->pos == i) && (color += 10))
					break ;
				else tmp = tmp->next;
			wattron(vm_window, COLOR_PAIR(color));
			wprintw(vm_window, "%02x", vm->arena[i]);
			wattroff(vm_window, COLOR_PAIR(color));
			waddch(vm_window, ' ');
			vm->arena[i] +=  vm->arena[i] != 0 ? color : 0; // test
		}
		i = -1;
		while (++i < vm->players)
			mvwprintw(vm_window, i + 1, SIZE_64 * 3 + 5, "player -%d : %s", i + 1, vm->champ[i]->name);
		mvwprintw(vm_window, ++i + 1, SIZE_64 * 3 + 5, "Cycles/second : %d", 1000 / speed);
		mvwprintw(vm_window, ++i + 1, SIZE_64 * 3 + 5, "Cycle : %d", cycle);
		mvwprintw(vm_window, ++i + 1, SIZE_64 * 3 + 5, "Cursors : %d", vm->curs);
		mvwprintw(vm_window, ++i + 1, SIZE_64 * 3 + 5, "players = %d", vm->players);
		mvwprintw(vm_window, ++i + 1, SIZE_64 * 3 + 5, "champs = %d", vm->champ[0]);
		mvwprintw(vm_window, ++i + 1, SIZE_64 * 3 + 5, "Cycle to die : %d", CYCLE_TO_DIE);
		mvwprintw(vm_window, ++i + 1, SIZE_64 * 3 + 5, "Cycle delta : %d", CYCLE_DELTA);
		mvwprintw(vm_window, ++i + 1, SIZE_64 * 3 + 5, "Lives : %d/%d", vm->champ, NBR_LIVE);
		mvwprintw(vm_window, ++i + 1, SIZE_64 * 3 + 5, "Cycles to check : %d", vm->champ);
		mvwprintw(vm_window, ++i + 1, SIZE_64 * 3 + 5, "Checks : %d/%d", vm->champ[1], MAX_CHECKS);
		wrefresh(vm_window);
		usleep(speed);
	}
	wclear(vm_window);
    endwin(); // завершение работы с ncurses
}
/*
Cursors : 2
Player -1 : Mikael Blomkvist
Last live :                   0
Lives in current period :     0
*/