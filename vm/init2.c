/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoye <djoye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 11:39:19 by sdoughnu          #+#    #+#             */
/*   Updated: 2020/01/24 17:58:21 by djoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int					exec_magic(int fd)
{
	t_4bytes		num;
	unsigned int	c;
	unsigned char	tmp;

	if (read(fd, &c, 4) <= 0)
		exit(!ft_printf("Magic read error\n"));
	num.hex = c;
	tmp = num.f.o1;
	num.f.o1 = num.f.o4;
	num.f.o4 = tmp;
	tmp = num.f.o2;
	num.f.o2 = num.f.o3;
	num.f.o3 = tmp;
	if (num.hex == COREWAR_EXEC_MAGIC)
		return (1);
	return (0);
}

void				replace_ch(t_vm *vm, int n, t_champion *ch)
{
	t_champion		*buf;
	t_champion		*tmp;
	int				i;

	i = n;
	buf = vm->champ[n - 1];
	vm->champ[n - 1] = ch;
	vm->champ[n - 1]->n = n;
	while (i < MAX_PLAYERS)
	{
		if (!vm->champ[i])
		{
			vm->champ[i] = buf;
			break ;
		}
		else if (!vm->champ[i]->n)
		{
			tmp = vm->champ[i];
			vm->champ[i] = buf;
			buf = tmp;
			free(tmp);
		}
		i++;
	}
}

void				champ_in_vm(t_champion *ch, t_vm *vm, int n)
{
	int				i;

	i = 0;
	if (n < 0)
	{
		while (i < MAX_PLAYERS && vm->champ[i])
			i++;
		vm->champ[i] = ch;
	}
	else
	{
		if (!vm->champ[n - 1])
		{
			vm->champ[n - 1] = ch;
			vm->champ[n - 1]->n = n;
		}
		else
			replace_ch(vm, n, ch);
	}
}

int					check_n(t_vm *vm, unsigned n)
{
	int				i;

	i = -1;
	while (++i < MAX_PLAYERS)
		if (vm->champ[i])
			if (vm->champ[i]->n == n)
				return (0);
	return (1);
}

int					check_ch_name(char **av, int i)
{
	int				l;

	l = ft_strlen(av[i]);
	if (av[i][l - 1] != 'r' || av[i][l - 2] != 'o' || av[i][l - 3] != 'c'
		|| av[i][l - 4] != '.')
		return (0);
	return (1);
}
