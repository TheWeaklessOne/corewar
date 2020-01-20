/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoye <djoye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 18:24:30 by djoye             #+#    #+#             */
/*   Updated: 2020/01/20 15:50:32 by djoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"
#include <ncurses.h>
//# define HEIGHT 0 //					(MEM_SIZE / 64 + 4)
//# define WIDTH	0 //				(64 * 3 + 5)
#define HEIGHT 300
#define WIDTH 300
//#define X 0
//#define Y 0
//#define Y_SUB 80

void	print_arena_test(t_vm *vm, int step)
{
    WINDOW      *vm_window;
    int         i;
    static int  speed = 10000;
    int         key;
	int			row;
	int			column;
	int			color;
	int			cycle;	
	
    initscr(); // перемещение курсора в стандартном экране y=10 x=30
	keypad(stdscr, true);
	nodelay(stdscr, true);
	curs_set(false);
	cbreak();
	noecho();
	//init_map(vm);
	//sub = newwin(HEIGHT, WIDTH / 4 + 10, 1, WIDTH + 6);
	//win_help = newwin(HEIGHT / 5, WIDTH, HEIGHT + 2, 2);
	//init_cursors(vm);
	//vm_window = newwin(NLINES, NCOLS, Y, X);
    vm_window = newwin(HEIGHT, WIDTH, 0, 0);
	cycle = 0;
    while (cycle++ < 2000)
    {
		i = -1;
        key = getch(); // ждём нажатия символа
        if (key == KEY_DOWN)
    	    speed < 200000 ? speed *= 2 : 0;
        if (key == KEY_UP)
    	   speed > 100 ? speed /= 2 : 0;
		column = 0;
		row = 1;
		start_color();
		init_pair(0, COLOR_WHITE, COLOR_BLACK);
		init_pair(1, COLOR_RED, COLOR_BLACK);
		init_pair(2, COLOR_GREEN, COLOR_BLACK);
		init_pair(3, COLOR_YELLOW, COLOR_BLACK);
		init_pair(4, COLOR_BLUE, COLOR_BLACK);
		while(++i < MEM_SIZE)
        {
			if (i % 64 == 0)
				wmove(vm_window, row++, 2);
			color = vm->map_color[i] == 0 ? 0 : vm->map_color[i];
			wattron(vm_window, COLOR_PAIR(color));
			wprintw(vm_window, "%02x", vm->arena[i]);
			wattroff(vm_window, COLOR_PAIR(color));
			waddch(vm_window, ' ');
			vm->arena[i] +=  vm->arena[i] != 0 ? color : 0; // test
		}
		
	//	wattron(vm_window, COLOR_RED);
	
		
//init_pair(1, color, COLOR_BLACK);
			//wbkgdset(vm_window, COLOR_PAIR(1));
	//wbkgdset(vm_window, COLOR_PAIR(1));
/*
 50
 0
Cursors : 2
Player -1 : Mikael Blomkvist
Last live :                   0
Lives in current period :     0

*/
		mvwprintw(vm_window, 3, 200, "Cycles/second : %d", 1000 / speed);
		mvwprintw(vm_window, 4, 200, "Cycle : %d", cycle);
		mvwprintw(vm_window, 5, 200, "Cursors : %d", vm->curs);

		mvwprintw(vm_window, 6, 200, "players = %d", vm->players);
		mvwprintw(vm_window, 7, 200, "champs = %d", vm->champ[0]);
		mvwprintw(vm_window, 8, 200, "Cycle to die : %d", CYCLE_TO_DIE);
		mvwprintw(vm_window, 9, 200, "Cycle delta : %d", CYCLE_DELTA);
		mvwprintw(vm_window, 10, 200, "Lives : %d/%d", vm->champ, NBR_LIVE);
		mvwprintw(vm_window, 11, 200, "Cycles to check : %d", vm->champ);
		mvwprintw(vm_window, 12, 200, "Checks : %d/%d", vm->champ[1], MAX_CHECKS);
		//wattroff(vm_window, COLOR_RED);
		wrefresh(vm_window);
		usleep(speed);
		
	}
	wclear(vm_window);
    endwin(); // завершение работы с ncurses
}