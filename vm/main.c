/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoye <djoye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 10:05:40 by sdoughnu          #+#    #+#             */
/*   Updated: 2020/01/23 16:26:55 by djoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int		flag(int *i, int ac, char **av, t_vm *vm)
{
	if (*i + 1 < ac && !ft_strncmp(av[*i], "-dump", 5))
	{
		vm->dump = ft_atoi(av[++(*i)]);
		if (vm->dump < 0)
			return (printf("Invalid option in flag [-dump]\n") - 31);
		(*i)++;
		return (1);
	}
	else if (*i < ac && !ft_strncmp(av[*i], "-v", 2))
	{
		vm->color = 1;
		(*i)++;
		return (1);
	}
	else if (*i + 1 < ac && !ft_strncmp(av[*i], "-d", 2))
	{
		vm->d = ft_atoi(av[++(*i)]);
		if (vm->d < 0)
			return (printf("Invalid option in flag [-d]\n") - 28);
		(*i)++;
		return (1);
	}
	if ((!ft_strncmp(av[*i], "-dump", 5) || !ft_strncmp(av[*i], "-d", 2))
		&& *i + 1 >= ac)
		return (printf("The flag is missing a number\n") - 29);
	return (1);
}

int		parser(t_vm *vm, int ac, char **av)
{
	int i;
	int n;

	i = 1;
	while (i < ac)
	{
		n = -1;
		if (!flag(&i, ac, av, vm))
			return (0);
		if (i + 1 < ac && !ft_strcmp(av[i], "-n"))
		{   
			n = ft_atoi(av[++i]);
			if (n > MAX_PLAYERS	|| n < 1 || !check_n(vm, n))
				return (printf("Invalid option in flag [-n]\n") - 28);
			i++;
		}
		if (i < ac && !init_champ(&i, av, n, vm))
			return(0);
	}
	return (1);
}

void		init(t_vm *vm)
{
	int i;

	i = -1;
	vm->dump = -1;
	vm->color = -1;
	vm->d = -1;
	vm->players = 0;
	vm->global = 0;
	vm->check = 0;
	while (++i < MAX_PLAYERS)
		vm->champ[i] = NULL;
}

int		main(int ac, char **av)
{
	t_vm		vm;

	if (ac < 2)
	{
		printf("usage: ./corewar [champ1, champ2 ...]\n");
		printf("    [-dump <num>]   dumps memory after N cycles\n");
		printf("    [-v]            visualization\n");
		printf("    [-n <num>]      set number of the next player\n");
		exit(0);
	}
	init(&vm);
	if (!(parser(&vm, ac, av)))
		exit(1);
	if (vm.players == 0)
		exit(printf("You have not entered champions\n") - 31);
	if (!build_arena(&vm))
		exit(0);
	if (!cur_init(&vm))
		exit(1);
	if (!war_coming(&vm))
		exit(0);
	exit(0);
}
