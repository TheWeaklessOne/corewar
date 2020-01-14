/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_champion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoughnu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 14:43:36 by sdoughnu          #+#    #+#             */
/*   Updated: 2020/01/13 14:43:46 by sdoughnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"



int 	main(int ac, char **av)
{
	int i;

	int fd = open(av[1], O_RDONLY);
	exec_magic(fd);
	printf("%x", COREWAR_EXEC_MAGIC);
	return (0);
}
