/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoye <djoye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 10:21:55 by sdoughnu          #+#    #+#             */
/*   Updated: 2020/01/15 18:26:43 by djoye            ###   ########.fr       */
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
	char 				*code;
}						t_champion;

typedef struct	s_vm
{
	int				dump;
	int				color;
	int				players;
	t_champion		*champ[MAX_PLAYERS];
	unsigned char	arena[MEM_SIZE];
	char			map_color[MEM_SIZE];
}				t_vm;

typedef struct	s_bit_field
{
	int			octet1 : 8;
	int			octet2 : 8;
	int			octet3 : 8;
	int			octet4 : 8;
	int			o_temp : 8;
}				t_bit_field;

typedef	union	u_4bytes
{
	t_bit_field field;
	int			hex;
}				t_4bytes;

int 	init_champ(int *i, char **av, int n, t_vm *vm);
void	champ_in_vm(t_champion *ch, t_vm *vm, int n);
int 	exec_magic(int fd);
int 	build_arena(t_vm *vm);
int 	check_n(t_vm *vm, int n);
int 	check_ch_name(char **av, int i);

#endif
