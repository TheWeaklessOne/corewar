/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stross <stross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:30:35 by stross            #+#    #+#             */
/*   Updated: 2020/02/08 15:37:21 by stross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	token_syntax_error(char *str, int line, int row)
{
	printf("Syntax error at token [TOKEN][%.3d:%.3d] INSTRUCTION \"%s\"\n", line, row, str); //FIXME printf
	exit(1);
}

void	token_label(char *str, int line, int row)
{
	printf("Unexpected token \"%s:\" LABEL at [%.3d:%.3d]\n", str, line, row); //FIXME printf
	exit(1);
}

void	insruction_token(char *str, int line, int row)
{
	char *print;

	print = ft_strcdup(str, ' ');
	printf("Invalid instruction at token [TOKEN][%.3d:%.3d] INSTRUCTION \"%s\"\n", line, row, print); //FIXME printf
	exit(1);
}

void	invalid_instruction(int num, char *str)
{
	printf("Invalid parameter %d for instruction %s\n", num, str); //FIXME printf
	exit(1);
}

void	invalid_ins_sim(int *arr, char *cpy, int mod)
{
	arr[1] += check_instructions(cpy) + (int)ft_strlen(g_op[mod - 1]);
	printf("Syntax error at token [TOKEN][%.3d:%.3d] INVALID INSTRUCTION\n", arr[0], arr[1]); //FIXME printf
	exit(1);
}