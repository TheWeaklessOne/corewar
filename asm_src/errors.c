/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stross <stross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 19:00:57 by stross            #+#    #+#             */
/*   Updated: 2020/02/25 12:40:48 by stross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		error_usage(void)
{
	write(2, "Usage: ./asm_src (champion.s|champion.cor)\n", 39);
	write(2, "\tchampion.s   — from assembly to bytecode\n", 44);
	write(2, "\tchampion.cor — from bytecode to assembly\n", 44);
	exit(1);
}

void		error_allocation(void)
{
	write(2, "Failed to allocate memory\n", 27);
	exit(1);
}

void		unexpected_token(int line, int row, char *str)
{
	char *token;

	token = ft_strcdup(str, ' ');
	write(2, "Unexpected token \"", 18);
	ft_putstr_fd(token, 2);
	write(2, "\" COMMAND at [", 14);
	ft_putnbr_fd(line, 2);
	write(2, ":", 1);
	ft_putnbr_fd(row, 2);
	write(2, "]\n", 2);
	exit(1);
}

static void	help_name_syntax(char *temp, int line, int row)
{
	write(2, "Syntax error at token [TOKEN][", 30);
	ft_putnbr_fd(line, 2);
	write(2, ":", 1);
	ft_putnbr_fd(row, 2);
	write(2, "] INSTRUCTION \"", 15);
	ft_putstr_fd(temp, 2);
	write(2, "\"\n", 2);
}

void		name_syntax(char *str, int line, int row, int mod)
{
	char	*temp;
	int		i;

	i = 0;
	str += (mod == 1 ? ft_strlen(NAME_CMD_STRING)
			: ft_strlen(COMMENT_CMD_STRING));
	while (ft_isspace(*str) && *str)
		str++;
	if (*str == '"')
		temp = ft_strdup(++str);
	else
	{
		temp = ft_strdup(str);
		while (temp[i] && temp[i] != '"')
			i++;
		if (temp[i] == '"')
			temp[i] = '\0';
	}
	help_name_syntax(temp, line, row);
	free(temp);
	exit(1);
}
