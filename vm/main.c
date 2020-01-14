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

#include "../includes/vm.h"

int		flag(int *i, int ac, char **av, t_vm *vm)
{
	if (!ft_strncmp(av[*i], "-dump", 5) && *i + 1 < ac)
	{
		vm->dump = ft_atoi(av[++(*i)]);
		if (vm->dump < 0)
			return (printf("Invalid option in flag [-dump]\n") - 31);
		(*i)++;
		return (1);
	}
	else if (!ft_strncmp(av[*i], "-v", 2))
	{
		vm->color = 1;
		(*i)++;
		return (1);
	}
	return (1);
}

int 	init_champ(int *i, char **av, int n, t_vm *vm)
{
	t_champion	*ch;
	int 		fd;
	static int 	x = -1;

	fd = open(av[*i], O_RDONLY);
	if (!exec_magic(fd))
		return (error_free(vm));
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
			//printf("ok\n");
			if (n > MAX_PLAYERS	|| n < 1)
				return (printf("Invalid option in flag [-n]\n") - 28);
			i++;
		}
		if (i < ac && !init_champ(&i, av, n, vm))
			return(0);
		i++;
	}
	return (1);
}

int		init(t_vm **vm)
{
	if (!(*vm = (t_vm*)malloc(sizeof(t_vm) * 1)))
		return (0);
	(*vm)->dump = -1;
	(*vm)->color = -1;
	return (1);
}

int		main(int ac, char **av)
{
	t_vm		*vm;

	if (ac < 2)
	{
		printf("usage: ./vm [champ1, champ2 ...]\n");
		exit(0);
	}
	if (!init(&vm))
		exit(1);
	if (!(parser(vm, ac, av)))
		exit(1);
//	printf("ok\n");
	exit(0);
}
