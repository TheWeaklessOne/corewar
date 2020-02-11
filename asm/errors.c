/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stross <stross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 19:00:57 by stross            #+#    #+#             */
/*   Updated: 2020/02/07 13:11:59 by stross           ###   ########.fr       */
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

void	unexpected_token(int line, int row, char *str)
{
	char *token;

	token = ft_strcdup(str, ' ');
	printf("Unexpected token \"%s\" COMMAND at [%.3d:%.3d]\n", token, line, row); //FIXME printf
	free(token);
	exit(1);
}

void	name_syntax(char *str, int line, int row)
{
	char	*temp;
	int		i;

	i = 0;
	str += ft_strlen(NAME_CMD_STRING);
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
	printf("Syntax error at token [TOKEN][%.3d:%.3d] INSTRUCTION \"%s\"\n", line, row, temp); // FIXME printf
	free(temp);
	exit(1);
}

void	length_error(int mod)
{
	if (mod == 1)
		printf("Champion name too long (Max length %d)\n", PROG_NAME_LENGTH); //FIXME printf
	if (mod == 2)
		printf("Champion comment too long (Max length %d)\n", COMMENT_LENGTH); //FIXME printf
	exit(1);
}