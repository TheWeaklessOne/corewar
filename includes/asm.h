/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stross <stross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:43:02 by stross            #+#    #+#             */
/*   Updated: 2020/02/14 14:28:29 by stross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "op.h"
# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>
# include <limits.h>
# include <string.h>

# define BUFF_SIZE 1024
# define ASM 2
# define DISASM 1

/*
** REG 1
** DIR 2
** IND 3
*/


/*
** LIVE 1
** AFF 2
** STI 3
** ADD 4
** SUB 5
** AND 6
** OR 7
** XOR 8
** ZJMP 9
** LDI 10
** ST 11
** FORK 12
** LLDI 13
** LLD 14
** LFORK 15
** LD 16
** TRASH 17
*/

extern char *g_op[17];

//enum e_parameters{ NONE, REG, DIR, IND };
//
//enum e_commands { LABEL, LIVE, AFF, STI, ADD, SUB, AND, OR, XOR,
//	ZJMP, LDI, ST, FORK, LLDI, LLD, LFORK, LD, TRASH };

typedef struct			s_oct
{
	unsigned char	at : 2;
	unsigned char	bt : 2;
	unsigned char	ct : 2;
	unsigned char	dt : 2;

}						t_oct;

typedef	union			u_oct
{
	t_oct			field;
	unsigned char	num;
}						t_one_byte;

typedef struct			s_bit_field
{
	int				octet1 : 8;
	int				octet2 : 8;
	int				octet3 : 8;
	int				octet4 : 8;
	int				o_temp : 8;
}					t_bit_field;

typedef	union			u_4bytes
{
	t_bit_field 	field;
	int				hex;
}					t_4bytes;

typedef struct			s_command
{
	bool				is_label;
	int					name;
	int					total_bytes;
	char				*command;
	int					byte_size;
	char				*label;
}						t_command;

typedef struct			s_asm_list
{
	t_command			*command;
	struct s_asm_list	*next;
}						t_asm_list;

typedef struct			s_head
{
	t_command			**commands;
	t_asm_list			*list;
	int					exec_size;
	unsigned char		name[PROG_NAME_LENGTH];
	bool				name_ex;
	unsigned char		comment[COMMENT_LENGTH];
	bool				comm_ex;
	char				*main_str;
	char				**split_str;
}						t_head;

char					*get_string(char **argv);
char 					*ft_strcdup(char *str, char c);
char					*label(char *str, int line, int row);
char					*get_comm_label(char *str);
void					validator(char **argv, t_head *head);
void					create_file(char **argv, t_head *head);
void					remove_comments(char **arr);
void					error_usage(void);
void					find_separator(char **cpy, int mod ,int num);
void					write_arg_type(char *str, int fd, int mod);
void					no_label_error(void);
void					length_error(int mod);
void 					create_struct(t_head *head);
void					write_reg(int fd, char *str);
void					write_exec_code_2b(int size, int fd);
void					handle_dir_2size(int fd, char *str, t_command *command, t_command **commands);
void					handle_dir(int fd, char *str, t_command *command, t_command **commands);
void					main_write(int fd, t_command *command, t_command **commands, int mod);
void					insruction_token(char *str, int line, int row);
void					get_comm_bytes(char *str, t_head *head, int line, int row);
void					get_name_bytes(char *str, t_head *head, int line, int row);
void					name_syntax(char *str, int line, int row);
void					invalid_instruction(int num, char *str);
void					token_syntax_error(char *str, int line, int row);
void					unexpected_token(int line, int row, char *str);
void					error_allocation(void);
void					write_exec_code(int size, int fd);
void					free_split(char **arr);
void					create_command(char *str, int mod, int byte_size, t_head *head);
void					token_label(char *str, int line, int row);
void					c_ld_lld(char *str, t_head *head, int mod, int *arr);
void					c_st(char *str, t_head *head, int mod, int *arr);
void					c_sti(char *str, t_head *head, int mod, int *arr);
void					c_ldi_lldi(char *str, t_head *head, int mod, int *arr);
void					c_live_zjmp_fork_lfork(char *str, t_head *head, int mod,int *arr);
void					c_add_sub(char *str, t_head *head, int mod, int *arr);
void					c_and_xor_or(char *str, t_head *head, int mod, int *arr);
void					c_aff(char *str, t_head *head, int mod, int *arr);
void					assembly(int fd, t_head *head);
void					invalid_ins_sim(int *arr, char *cpy, int mod);
void					free_head(t_head *head);
void					write_command(int fd, t_command *command, t_command **commands);
char					**split(char *str, char sep);
int						ft_isspace(char ch);
int						get_label_distance(t_command *command, t_command **commands, char *label, int *mod);
int						find_command(char *str, char mod);
int						ft_strchlen(char *str, char ch);
int						strstr_zero(char *hey, char *need);
int						check_instructions(char *str);
int						instruction_size(char ch, int size);

void					ft_list_push_back(t_asm_list **begin_list, t_command *command);
void					ft_list_clear(t_asm_list **begin_list);

#endif