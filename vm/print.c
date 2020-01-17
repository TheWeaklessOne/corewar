/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoye <djoye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 18:24:30 by djoye             #+#    #+#             */
/*   Updated: 2020/01/17 15:32:48 by djoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"
#include <ncurses.h>
#include <panel.h>
#define NLINES 120
#define NCOLS 120
#define X 0
#define Y 0
#define Y_SUB 80

void	arena_test(t_vm *vm, int step)
{
<<<<<<< HEAD
    WINDOW      *orig;
    WINDOW      *sub;
    int         i;
    static int  speed;
    int         ch;

    speed = 1000;
    initscr(); // перемещение курсора в стандартном экране y=10 x=30
	orig = newwin(NLINES, NCOLS, Y, X);
    sub =  subwin(orig, NLINES, NCOLS,  Y, X);
    
    keypad(stdscr, TRUE);

    i = 0;
    while (i++ < 300)
    {
        noecho();
        cbreak();
        halfdelay(1);
        if (getch() == KEY_UP)
    	    speed > 10 ? speed /= 2 : 0;
        if (getch() == KEY_DOWN)
    	    speed < 200000 ? speed *= 2 : 0;
        start_color();
        init_pair(1, COLOR_RED, COLOR_BLACK);
        init_pair(2, COLOR_YELLOW, COLOR_BLACK);
        wbkgdset(orig, COLOR_PAIR(1));
        wbkgdset(sub, COLOR_PAIR(2));

        mvwprintw(orig, X, Y, "first_window, %d = %d", speed, i);
        mvwprintw(sub, X, Y_SUB, "second_window, %d = %d", speed, i);
        wrefresh(orig);
        wrefresh(sub);
        usleep(speed);
        wclear(orig);
        wclear(sub);
    }
=======
//    WINDOW  *orig;
//    WINDOW  *sub;
//    int     i;
//
//    start_color();
//    init_pair(1, COLOR_RED, COLOR_BLUE);
//    init_pair(2, COLOR_GREEN, COLOR_RED);
//    init_pair(3, COLOR_YELLOW, COLOR_GREEN);
//    init_pair(3, COLOR_BLUE, COLOR_GREEN);
//    initscr(); // перемещение курсора в стандартном экране y=10 x=30
//	orig = newwin(NLINES, NCOLS, Y, X);
//    sub =  subwin(orig, NLINES, NCOLS,  Y, X);
//
//
//    start_color();
//    init_pair(1, COLOR_RED, COLOR_BLACK);
//	wbkgdset(orig, COLOR_PAIR(1));
//    wbkgdset(sub, COLOR_PAIR(1));
//    mvwprintw(orig, 0, 0, "111111111");
//    mvwprintw(sub, 10, 10, "222222222");
//	wrefresh(orig);
//    wrefresh(sub);
//    usleep(SPEED);
//    wclear(orig);
//    wclear(sub);
//    mvwprintw(sub, 0, 0, "222222222");
//    wrefresh(sub);
//    usleep(SPEED);
//    wclear(sub);
//    start_color();
//    print_arena(vm, step);
//    init_pair(1, COLOR_RED, COLOR_BLACK);
//    mvwprintw(orig, 0, 0, "33333333333334");
//    wrefresh(orig);

>>>>>>> f02f280dbff10fb1f914fbd052ab5d053d5b3492
/*
	while (i < MEM_SIZE)
	{
		if (i == 0 || (i % 64) == 0)
			printf("0x%0.4x : ", i);
		if (vm->color == 1 && vm->map_color[i] == 1)
			printf("%0.2x", vm->arena[i]);
		else if (vm->color == 1 && vm->map_color[i] == 2)
			printf("\e[32m%0.2x", vm->arena[i]);
		else if (vm->color == 1 && vm->map_color[i] == 3)
			printw("\e[33m%0.2x", vm->arena[i]);
		else if (vm->color == 1 && vm->map_color[i] == 4)
			printw("\e[34m%0.2x", vm->arena[i]);
		else
			printw(orig, "\e[0m%0.2x", vm->arena[i]);
		if ((i + 1) % 64 == 0 && i != 0)
			printw("\e[0m\n");
		else printw("\e[0m ");
		i++;
	}
    */

    //getch(KEY_UP); // ждём нажатия символа
    endwin(); // завершение работы с ncurses
}