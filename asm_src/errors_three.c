/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_three.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stross <stross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 11:50:31 by stross            #+#    #+#             */
/*   Updated: 2020/02/25 11:50:31 by stross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	no_label_error(void)
{
	write(2, "Unknown label\n", 14);
	exit(1);
}

void	error_reg_overflow(int line)
{
	write(2, "Line [", 6);
	ft_putnbr_fd(line, 2);
	write(2, "] error: invalid register variable\n", 35);
	exit(1);
}

void	error_argument_overflow(int line)
{
	write(2, "Line [", 6);
	ft_putnbr_fd(line, 2);
	write(2, "] error: invalid argument\n", 26);
	exit(1);
}

void	diss_not_ready(void)
{
	write(2, "Disassambly mode is not ready yet\n", 34);
	exit(1);
}

void	length_error(int mod)
{
	if (mod == 1)
	{
		write(2, "Champion name too long (Max length ", 35);
		ft_putnbr_fd(PROG_NAME_LENGTH, 2);
		write(2, ")\n", 2);
	}
	if (mod == 2)
	{
		write(2, "Champion comment too long (Max length ", 38);
		ft_putnbr_fd(COMMENT_LENGTH, 2);
		write(2, ")\n", 2);
	}
	exit(1);
}
