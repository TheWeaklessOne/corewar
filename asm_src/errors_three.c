/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_three.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stross <stross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 11:50:31 by stross            #+#    #+#             */
/*   Updated: 2020/02/19 14:04:04 by stross           ###   ########.fr       */
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
	printf("Line [%0.3d] error: invalid register variable\n", line);//FIXME prijtf
	exit(1);
}

void	error_argument_overflow(int line)
{
	printf("Line [%0.3d] error: invalid argument\n", line);//FIXME prijtf
	exit(1);
}
