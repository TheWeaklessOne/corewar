/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoughnu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 10:05:40 by sdoughnu          #+#    #+#             */
/*   Updated: 2020/01/11 10:05:42 by sdoughnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		parser(t_vm *vm, int ac, char **av)
{
	int i;

	i = 1;
	while (i++ < c)
	{
		if (i + 2 < c)
	}
}

int		main(int ac, char **av)
{
	t_vm		*vm;

	if (ac < 2)
	{
		printf("usage: ./vm [champ1, champ2 ...]\n");
		exit(0);
	}
	if (!(vm = (t_vm*)malloc(sizeof(t_vm))))
		exit(1);
	if (!(parser(vm, ac, av)))
		exit(1);
	exit(0);
}
