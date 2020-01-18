/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoye <djoye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 18:24:30 by djoye             #+#    #+#             */
/*   Updated: 2020/01/18 20:16:23 by djoye            ###   ########.fr       */
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
    	   speed > 10 ? speed /= 2 : 0;
		column = 0;
		row = 0;
		while(++i < MEM_SIZE)
        {
			//use_default_colors();
			//start_color();
			color = vm->map_color[i] == 0 ? 7 : vm->map_color[i];
			wattron(vm_window, color);
			//init_pair(1, color, COLOR_BLACK);
			//wbkgdset(vm_window, COLOR_PAIR(1));
			mvwprintw(vm_window, row, column += 3 , "%02x", vm->arena[i]);
			vm->arena[i] +=  vm->arena[i] != 0 ? 1 : 0; // test
			if (i != 0 && (i + 1) % 64 == 0)
			{
				row++;
				column = 0;
			}
			//wrefresh(vm_window);
		}
		mvwprintw(vm_window, 3, 200, "cycles = %d", cycle);
		mvwprintw(vm_window, 4, 200, "speed = %d", speed);
		mvwprintw(vm_window, 5, 200, "players = %d", vm->players);
		mvwprintw(vm_window, 6, 200, "champs = %d", vm->champ);
		wrefresh(vm_window);
		usleep(speed);
	}
	wclear(vm_window);
    endwin(); // завершение работы с ncurses
}