/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stross <stross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 18:50:49 by stross            #+#    #+#             */
/*   Updated: 2020/02/10 13:33:34 by stross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char *g_op[17] = {"live", "aff", "sti", "add", "sub", "and", "or", "xor",
				"zjmp", "ldi", "st", "fork", "lldi", "lld", "lfork", "ld"};


static int	check_is_it_comm(char *str)
{
	int		mod;

	mod = 0;
	if ((mod = find_command(str, 'z')))
	{
		str += ft_strlen(g_op[mod - 1]);
		if (*str == ' ' || *str == '%' || *str == 'r' || *str == '\t')
			return (1);
	}
	return (0);
}

static int	check_label_chars(char *str)
{
	int		i;
	bool	flag;

	while (*str)
	{
		i = 0;
		flag = false;
		while (LABEL_CHARS[i])
		{
			if (LABEL_CHARS[i] == *str)
				flag = true;
			i++;
		}
		if (!flag)
			return (1);
		str++;
	}
	return (0);
}

char	*label(char *str, int line, int row)
{
	int		i;
	int 	si;
	int		ti;
	char 	*cpy;
	bool	flag;

	i = 0;
	si = 0;
	while (str[i])
	{
		if (str[i] == LABEL_CHAR)
			break ;
		i++;
	}
	if (check_is_it_comm(str))
		return (NULL);
	if (!str[i])
		return (NULL);
	while (si < i)
	{
		flag = false;
		ti = 0;
		while (LABEL_CHARS[ti])
		{
			if (str[si] == LABEL_CHARS[ti])
				flag = true;
			ti++;
		}
		if (!flag)
			if (!find_command(str + i, 'f') && !*str)
				token_label(ft_strcdup(str, LABEL_CHAR), line, row);
		si++;
	}
	cpy = ft_strcdup(str, LABEL_CHAR);
	if (check_label_chars(cpy))
		token_label(ft_strcdup(str, LABEL_CHAR), line, row);
	return (cpy);
}

int		find_command(char *str, char mod)
{
	int i;

	i = 0;
	if (mod == 'f')
	{
		while (g_op[i])
		{
			if (ft_strstr(str, g_op[i]))
				return (i + 1);
			i++;
		}
	}
	else if (mod == 'z')
	{
		while (g_op[i])
		{
			if (strstr_zero(str, g_op[i]))
				return (i + 1);
			i++;
		}
	}
	return (0);
}

void	get_comm_bytes(char *str, t_head *head, int line, int row)
{
	int		qm_count;
	int		i;

	head->comm_ex = true;
	qm_count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
			qm_count++;
		i++;
	}
	if (qm_count != 2)
		name_syntax(str, line, row);
	else
	{
		i = 0;
		str = ft_strchr(str, '"');
		str++;
		while (*str && *str != '"')
		{
			if (i > COMMENT_LENGTH)
				length_error(2);
			head->comment[i++] = *str++;
		}
	}
}

void	get_name_bytes(char *str, t_head *head, int line, int row)
{
	int		qm_count;
	int		i;

	head->name_ex = true;
	qm_count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
			qm_count++;
		i++;
	}
	if (qm_count != 2)
		name_syntax(str, line, row);
	else
	{
		i = 0;
		str = ft_strchr(str, '"');
		str++;
		while (*str && *str != '"')
		{
			if (i > PROG_NAME_LENGTH)
				length_error(1);
			head->name[i++] = *str++;
		}
	}
}