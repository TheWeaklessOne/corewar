/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoye <djoye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 10:21:55 by sdoughnu          #+#    #+#             */
/*   Updated: 2020/02/25 18:08:01 by djoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <unistd.h>
# include <fcntl.h>

# include "./op.h"
# include "../libft/libft.h"
# include <ncurses.h>
# include <sys/ioctl.h>

# define SIZE_64				64
# define HEIGHT (MEM_SIZE / SIZE_64 + 1)
# define WIDTH	(SIZE_64 * 3 + 23)
# define SUB (SIZE_64 * 3 + 3)
# define KEY_ESC 27
# define KEY_STEP 10

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

typedef	union		u_2bytes
{
	t_bit_field		f;
	short			hex;
}					t_2bytes;

typedef struct		s_short
{
	char			o1;
	char			o2;
}					t_short;

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
	int				dir_size;
}					t_op;

typedef struct		s_cur
{
	int				id;
	int				p;
	int				pos;
	int				carry;
	unsigned char	operation;
	int				reg[REG_NUMBER];
	int				cyc_before_op;
	unsigned		last_cyc_live;
	int				arg_size[3];
	unsigned		args_type[4];
	int				args[3];
	struct s_cur	*next;
}					t_cur;

typedef struct		s_vm
{
	int				dump;
	int				d;
	int				a;
	int				l;
	long			dump_count;
	long			d_count;
	int				color;
	int				zj;
	int				players;
	unsigned long	global;
	t_champion		*champ[MAX_PLAYERS];
	char			arena[MEM_SIZE];
	char			map_color[MEM_SIZE];
	int				cycles_to_die;
	int				checks;
	unsigned int	live_count;
	unsigned long	last_live;
	t_cur			*curs;
	unsigned		curs_alive;
	t_champion		*last_champ;
	int				speed;
	size_t			len_name;
	int				width;
	int				step;
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
int					check_n(t_vm *vm, unsigned n);
int					check_ch_name(char **av, int i);

int					cur_init(t_vm *vm);
void				id_cur_flag_l(t_cur *c);
t_cur				*cur_remove_at(t_cur *cur, int at);
t_cur				*cur_at(t_cur *cur, int at);
void				delete_deads(t_vm *vm);

int					print_arena(t_vm *vm, int size);
int					war_coming(t_vm *v);
int					war(t_vm *v, int check_count);

void				do_op(t_vm *vm, t_cur *cur);
int					check_op(t_vm *vm, t_cur *cur);

t_4bits				swap_bits(unsigned char nb);
int					read_t_dir(t_vm *vm, int pos, int size);
int					read_t_ind(t_vm *vm, int pos, int cpos);
void				read_args(t_vm *v, t_cur *c);
void				get_arg_types(unsigned char c, unsigned *args);

int					skip_uncorrect(t_cur *cur, const t_op *op);
int					print_fd(const char *s, int fd);
int					error_in(const char *s1, const char *s2, int fd);
int					print_fd2(const char *s, int fd);

void				l_for_sti(t_vm *vm, t_cur *cur);
void				color_map_sti(t_vm *vm, int skip, t_cur *cur);
void				place_arena_st(int skip, t_cur *cur,
					t_4bytes arg, t_vm *vm);

/*
** --------------------------visualization--------------------------
*/

WINDOW				*init_visu(WINDOW *vm_window, t_vm *vm);
void				remote(WINDOW *vm_window, t_vm *vm);
void				print_visu(WINDOW *vm_window, t_vm *vm, int flag);
void				print_matrix(WINDOW *vm_window, t_vm *vm);
void				print_sub_win(t_vm *vm, WINDOW *vm_window);
void				small_screen(WINDOW *vm_window, t_vm *vm);
void				max_name(t_vm *vm);
void				pause_step(WINDOW *vm_window, t_vm *vm);

#endif
