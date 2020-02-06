/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stross <stross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 19:00:57 by stross            #+#    #+#             */
/*   Updated: 2020/01/16 13:31:36 by stross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	error_usage(void)
{
	write(2, "Usage: ./asm (champion.s|champion.cor)\n", 40);
	write(2, "\tchampion.s   — from assembly to bytecode\n", 44);
	write(2, "\tchampion.cor — from bytecode to assembly\n", 44);
	exit(1);
}

void	error_allocation(void)
{
	write(2, "Failed to allocate memory\n", 27);
	exit(1);
}