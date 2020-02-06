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
	char			*code;
}					t_champion;

typedef struct		s_bit_field
{
	char			o1;
	char			o2;
	char			o3;
	char			o4;
}					t_bit_field;

typedef	union		u_4bytes
{
	t_bit_field		f;
	int				hex;
}					t_4bytes;

typedef struct		s_arg
{
	unsigned		a0 : 2;
	unsigned		a1 : 2;
	unsigned		a2 : 2;
	unsigned		a3 : 2;
}					t_arg;

typedef	union		u_4bits
{
	t_arg			f;
	unsigned char	arg;
}					t_4bits;

typedef struct		s_op
{
	char			*name;
	int				arg_count;
	unsigned		arg_type[3];
	int				code;
	int				need_cycles;
	int				code_type_arg;
	int				dir_size; // 0 это 4, 1 это 2
}					t_op;

typedef struct		s_cur
{
	int				id;
	int				pos;
	int				carry;
	unsigned char	operation;
	int				reg[REG_NUMBER];
	int				cyc_before_op;
	unsigned		last_cyc_live;
	struct s_cur	*next;
	int				arg_size[3];
	unsigned		args_type[4];
	int				args[3];
}					t_cur;

typedef struct		s_vm
{
	int				dump;
	int				d;
	int				color;
	int				players;
	unsigned long	global;
	t_champion		*champ[MAX_PLAYERS];
	char			arena[MEM_SIZE];
	char			map_color[MEM_SIZE];
	int				cycles_to_die;
	int				checks;
	unsigned int	live_count;
	t_cur			*curs;
	unsigned		curs_alive;// количество живых кареток
	t_champion		*last_champ;
}					t_vm;

extern const t_op	g_op_tab[17];

void				do_live(t_vm *vm, t_cur *cur);
void				do_ld(t_vm *vm, t_cur *cur);
void				do_st(t_vm *vm, t_cur *cur);
void				do_add(t_vm *vm, t_cur *cur);
void				do_sub(t_vm *vm, t_cur *cur);
void				do_and(t_vm *vm, t_cur *cur);
void				do_or(t_vm *vm, t_cur *cur);
void				do_xor(t_vm *vm, t_cur *cur);
void				do_zjmp(t_vm *vm, t_cur *cur);
void				do_ldi(t_vm *vm, t_cur *cur);
void				do_sti(t_vm *vm, t_cur *cur);
void				do_fork(t_vm *vm, t_cur *cur);
void				do_lld(t_vm *vm, t_cur *cur);
void				do_lldi(t_vm *vm, t_cur *cur);
void				do_lfork(t_vm *vm, t_cur *cur);
void				do_aff(t_vm *vm, t_cur *cur);

int					init_champ(int *i, char **av, int n, t_vm *vm);
void				champ_in_vm(t_champion *ch, t_vm *vm, int n);
int					exec_magic(int fd);
int					build_arena(t_vm *vm);
int					check_n(t_vm *vm, int n);
int					check_ch_name(char **av, int i);

int					cur_init(t_vm *vm);
t_cur				*cur_remove_at(t_cur *cur, int at);
t_cur				*cur_at(t_cur *cur, int at);
void				delete_deads(t_vm *vm);

void				print_arena_test(t_vm *vm, int step);
int					print_arena(t_vm *vm, int step, int size);
int					war_coming(t_vm *v);

void				do_op(t_vm *vm, t_cur *cur);
int					check_op(t_vm *vm, t_cur *cur);

t_4bits				swap_bits(unsigned char nb);
int					read_t_dir(t_vm *vm, int pos, int size);
int					read_t_ind(t_vm *vm, int pos, int cpos);
int					get_t_ind(t_vm *vm, int pos);
void				read_args(t_vm *v, t_cur *c);
void				get_arg_types(unsigned char c, unsigned *args);

#endif
