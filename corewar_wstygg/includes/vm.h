/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoye <djoye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 10:21:55 by sdoughnu          #+#    #+#             */
/*   Updated: 2020/01/24 17:58:22 by djoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <time.h>
# include <stdbool.h>

# include "./op.h"
# include "../libft/libft.h"


typedef struct		s_champion
{
	unsigned int	n;
	char			name[PROG_NAME_LENGTH + 1];
	char			com[COMMENT_LENGTH + 1];
	unsigned int	size;
	unsigned		last_alive;
	char			*code;
}					t_champion;

typedef struct		s_bit_field
{
	int				octet1 : 8;
	int				octet2 : 8;
	int				octet3 : 8;
	int				octet4 : 8;
}					t_bit_field;

typedef struct		s_byte
{
	unsigned		nb : 1;
}					t_byte;

typedef	union		u_kek
{
	t_byte			bytes[32];
	int32_t 		nb;
}					t_kek;

typedef	union		u_4bytes
{
	t_bit_field		field;
	int				hex;
}					t_4bytes;

typedef struct		s_arg
{
	unsigned 	arg_0 : 2;
	unsigned 	arg_1 : 2;
	unsigned 	arg_2 : 2;
	unsigned 	arg_3 : 2;
}					t_arg;

typedef	union		u_4bits
{
	t_arg			field;
	unsigned char	arg;
}					t_4bits;

typedef struct		s_op
{
	char			*name;
	int				arg_count;
	unsigned		arg_type[3];
	int				code;
	int				need_cycles;
	char			*opisanie;
	int				code_type_arg;
	int				dir_size; // 0 это 4, 1 это 2
}					t_op;

typedef struct		s_cur
{
	int				id;
	int				id_player;
	unsigned		pos;		//program counter "PC"
	int				step;
	int				carry;
	unsigned char	operation;
	unsigned		reg[REG_NUMBER];
	int				cyc_before_op;
	unsigned		last_cyc_live;
	struct s_cur	*next;
	t_4bits			code_arg;
	int				arg_size[3];
	unsigned		args_type[4];
	unsigned		args[3];
}					t_cur;

typedef struct		s_vm
{
	int				dump;
	int				d;
	int				color;
	int				players;
	unsigned long	global;
	t_champion		*champ[MAX_PLAYERS];
	unsigned char	arena[MEM_SIZE];
	char			map_color[MEM_SIZE];
	int				cycles_to_die;
	int				checks;
	unsigned int	live_count;
	t_cur			*curs;
	unsigned		curs_alive;		// количество живых кареток
}					t_vm;

int					init_champ(int *i, char **av, int n, t_vm *vm);
void				champ_in_vm(t_champion *ch, t_vm *vm, int n);
int					exec_magic(int fd);
int					build_arena(t_vm *vm);
int					check_n(t_vm *vm, int n);
int					check_ch_name(char **av, int i);

int					cur_init(t_vm *vm);

void				print_arena_test(t_vm *vm, int step);
int					print_arena(t_vm *vm, int step, int size);
int					war_coming(t_vm *vm);

int					check_arg(unsigned char id_op, unsigned char arg, const t_op op_tab[16]);

#endif
