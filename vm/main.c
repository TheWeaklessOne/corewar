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
	while (++i < MAX_PLAYERS)
		vm->champ[i] = NULL;
}

int		main(int ac, char **av)
{
	t_op    op_tab[17] =
{
	{"live",	1, {T_DIR},												  1, 10, "alive", 0, 0},
	{"ld",		2, {T_DIR | T_IND, T_REG}, 								  2, 5, "load", 1, 0},
	{"st",		2, {T_REG, T_IND | T_REG}, 								  3, 5, "store", 1, 0},
	{"add",		3, {T_REG, T_REG, T_REG}, 							      4, 10, "addition", 1, 0},
	{"sub",		3, {T_REG, T_REG, T_REG}, 								  5, 10, "soustraction", 1, 0},
	{"and",		3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6, "et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or",		3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,	"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor",		3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,	"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp",	1, {T_DIR}, 											  9, 20, "jump if zero", 0, 1},
	{"ldi",		3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 		  10, 25,"load index", 1, 1},
	{"sti",		3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},		  11, 25, "store index", 1, 1},
	{"fork",	1, {T_DIR},												  12, 800, "fork", 0, 1},
	{"lld",		2, {T_DIR | T_IND, T_REG},								  13, 10, "long load", 1, 0},
	{"lldi",	3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},         14, 50, "long load index", 1, 1},
	{"lfork",	1, {T_DIR},												  15, 1000, "long fork", 0, 1},
	{"aff",		1, {T_REG},												  16, 2, "aff", 1, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0}
};

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
	printf ("%d\n", check_arg(op_tab, 11, 104));
	if (!cur_init(&vm))
		exit(1);
	if (!war_coming(&vm))
		exit(1);
	exit(0);
}

//int     check_arg(t_op *op_tab, unsigned char id_op, unsigned char arg);