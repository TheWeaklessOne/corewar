/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stross <stross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:30:35 by stross            #+#    #+#             */
/*   Updated: 2020/02/25 11:39:29 by stross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	token_syntax_error(char *str, int line, int row)
{
	write(2, "Syntax error at token [TOKEN][", 30);
	ft_putnbr_fd(line, 2);
	write(2, ":", 1);
	ft_putnbr_fd(row, 2);
	write(2, "] INSTRUCTION \"", 15);
	ft_putstr_fd(str, 2);
	write(2, "\"\n", 2);
	exit(1);
}

void	token_label(char *str, int line, int row)
{
	write(2, "Unexpected token \"", 18);
	ft_putstr_fd(str, 2);
	write(2, "\" LABEL at [", 12);
	ft_putnbr_fd(line, 2);
	write(2, ":", 1);
	ft_putnbr_fd(row, 2);
	write(2, "]\n", 2);
	exit(1);
}

void	insruction_token(char *str, int line, int row)
{
	char *print;

	print = ft_strcdup(str, ' ');
	write(2, "Invalid instruction at token [TOKEN][", 37);
	ft_putnbr_fd(line, 2);
	write(2, ":", 1);
	ft_putnbr_fd(row, 2);
	write(2, "] INSTRUCTION \"", 15);
	ft_putstr_fd(print, 2);
	write(2, "\"\n", 2);
	exit(1);
}

void	invalid_instruction(int num, char *str)
{
	write(2, "Invalid parameter ", 18);
	ft_putnbr_fd(num, 2);
	write(2, " for instruction ", 17);
	ft_putstr_fd(str, 2);
	write(2, "\n", 1);
	exit(1);
}

void	invalid_ins_sim(int *arr, char *cpy, int mod)
{
	arr[1] += check_instructions(cpy) + (int)ft_strlen(g_op[mod - 1]);
	write(2, "Syntax error at token [TOKEN][", 30);
	ft_putnbr_fd(arr[0], 2);
	write(2, ":", 1);
	ft_putnbr_fd(arr[1], 2);
	write(2, "] INVALID INSTRUCTION\n", 22);
	exit(1);
}
