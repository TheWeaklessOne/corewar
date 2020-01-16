/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stross <stross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:43:02 by stross            #+#    #+#             */
/*   Updated: 2020/01/16 13:21:29 by stross           ###   ########.fr       */
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
# define ASM 1
# define DISASM 2

char	*get_string(char **argv);
char	*validator(int argc, char **argv);
void	create_file(char *str , char *filename);
void	error_usage(void);
void	error_allocation(void);
void	free_split(char **arr);
void	assembly(int fd, char *str);

#endif
