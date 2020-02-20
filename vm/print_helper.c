/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoye <djoye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 13:29:34 by djoye             #+#    #+#             */
/*   Updated: 2020/02/20 13:33:43 by djoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

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
		exit(0);
	}
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
	vm->width = WIDTH + (vm->len_name > 7 ? vm->len_name - 6 : 0);
}

void			pause_step(WINDOW *vm_window, t_vm *vm)
{
	int			key;

	vm->step = 1;
	while (vm->step && (key = getch()))
	{
		if (key == KEY_ESC)
			exit(endwin());
		else if (((key == ' ' || key == '0') && (vm->step = 0)) ||
		(key == KEY_STEP && (vm->step = 1)))
			break ;
		else if ((key == KEY_DOWN || key == '-') && vm->speed > 1)
			vm->speed--;
		else if ((key == KEY_UP || key == '+') && vm->speed < 9)
			vm->speed++;
		else if (key >= '1' && key <= '9')
			vm->speed = key - 48;
		print_visu(vm_window, vm, 1);
	}
}
