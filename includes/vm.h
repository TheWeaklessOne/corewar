/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoughnu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 10:21:55 by sdoughnu          #+#    #+#             */
/*   Updated: 2020/01/11 10:21:57 by sdoughnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <stdio.h>
# include <unistd.h>
# include "op.h"
# include "../libft/libft.h"
# include <fcntl.h>

typedef struct			s_champion
{
	unsigned int		n;
	char				name[PROG_NAME_LENGTH + 1];
	char				com[COMMENT_LENGTH + 1];
	unsigned int		size;
}						t_champion;

typedef struct	s_vm
{
	int			dump;
	int			color;
	t_champion	*champ[MAX_PLAYERS];
}				t_vm;

int 	init_champ(int *i, char **av, int n, t_vm *vm);

#endif
