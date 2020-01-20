/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoye <djoye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 10:21:55 by sdoughnu          #+#    #+#             */
/*   Updated: 2020/01/18 14:02:33 by djoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <stdio.h>
# include <unistd.h>
# include "op.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <time.h>
# include <stdbool.h>

typedef struct			s_champion
{
	unsigned int		n;
	char				name[PROG_NAME_LENGTH + 1];
	char				com[COMMENT_LENGTH + 1];
	unsigned int		size;
	char 				*code;
}						t_champion;

typedef struct		s_cur
{
	int				id;
	int 			id_player;
	int 			pos;
	int 			carry;
	int 			reg[REG_NUMBER];
	int 			cyc_before_op;
	int 			last_cyc_live;
	struct s_cur	*next;
}					t_cur;

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

typedef struct	s_op
{
	char 			*name;
	int				arg_count;
	int				arg_type;
	int 			code;
	int 			need_cycles;
	char 			*opisanie;
	int 			code_type_arg;
	int 			tdir_size; // 0 это 4, 1 это 2
}				t_op;

typedef struct	s_vm
{
	int				dump;
	int				color;
	int				players;
	int 			global;
	t_champion		*champ[MAX_PLAYERS];
	unsigned char	arena[MEM_SIZE];
	char			map_color[MEM_SIZE];
	t_cur			*curs;
}				t_vm;
/*
typedef struct		s_vs
{
	t_bool			is_running;
	int				speed;
	WINDOW			*win_arena;
	WINDOW			*win_info;
	WINDOW			*win_help;
	int				cursor_pos;
	char			map[MEM_SIZE];
	int				button;
	clock_t			time;
	char			aff_symbol;
	int				player;
	t_bool			sounds;
	t_bool			display_help;
}					t_vs;
*/
int 	init_champ(int *i, char **av, int n, t_vm *vm);
void	champ_in_vm(t_champion *ch, t_vm *vm, int n);
int 	exec_magic(int fd);
int 	build_arena(t_vm *vm);
int 	check_n(t_vm *vm, int n);
int 	check_ch_name(char **av, int i);

int 	cur_init(t_vm *vm);

void	print_arena_test(t_vm *vm, int step);
void	print_arena(t_vm *vm, int step);

#endif
