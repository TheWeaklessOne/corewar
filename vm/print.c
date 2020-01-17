/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoye <djoye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 18:24:30 by djoye             #+#    #+#             */
/*   Updated: 2020/01/16 20:14:27 by djoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"
#include <ncurses.h>
#include <panel.h>
#define NLINES 100
#define NCOLS 100
#define X 1
#define Y 1
#define X_SUB 1
#define Y_SUB 80
#define SPEED 500000*4

void	arena_test(t_vm *vm, int step)
{
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
	//char check = -1;
	//printf("%hhu\n", check);
	//printf("\033c");
  //  refresh(); // обновить
 //   getch(); // ждём нажатия символа
 //   endwin(); // завершение работы с ncurses
}