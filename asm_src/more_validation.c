/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stross <stross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 12:33:59 by stross            #+#    #+#             */
/*   Updated: 2020/02/19 15:16:09 by stross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static long	ft_atol(const char *str)
{
	int		i;
	int		sign;
	long	res;

	sign = 1;
	res = 0;
	i = 0;
	while (*str == ' ' || (*str > 8 && *str < 14))
		str++;
	if (*str == '-' || *str == '+')
		sign = (*str++ == '-' ? -1 : 1);
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str++ - '0');
		i += (res ? 1 : 0);
		if (i > 19 || res < 0 || (i && !res))
			return (sign == 1 ? -1 : 0);
	}
	return (sign * res);
}

static int	check_other_arguments(char *str)
{
	int		i;
	long	num;

	i = 0;
	if (*str == DIRECT_CHAR)
		str++;
	if (*str == LABEL_CHAR)
		return (0);
	num = ft_atol(str);
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
		str++;
	while (*str && *str != SEPARATOR_CHAR && *str != ' ')
	{
		if (*str >= '0' && *str <= '9')
			i++;
		if (!(*str >= '0' && *str <= '9'))
			return (1);
		str++;
	}
	if (num > UINT_MAX || num < INT_MIN || i > 10)
		return (1);
	return (0);
}

static int	check_reg_num(char *str)
{
	int		i;
	long	num;

	if (*str == 'r')
		str++;
	num = ft_atol(str);
	if (num < 0)
		return (1);
	i = 0;
	while (*str && *str != SEPARATOR_CHAR && *str != ' ')
	{
		if (*str >= '0' && *str <= '9')
			i++;
		if (!(*str >= '0' && *str <= '9'))
			return (1);
		str++;
	}
	if (i > 2)
		return (1);
	else
		return (0);
}

static void	validate_numbers(t_command *command, int line)
{
	char		*cpy;
	int			i;

	i = -1;
	cpy = command->command + ft_strlen(g_op[command->name - 1]);
	while (i++ != 3)
	{
		while (ft_isspace(*cpy))
			cpy++;
		if (*cpy == 'r')
		{
			if (check_reg_num(cpy))
				error_reg_overflow(line);
		}
		else if (*cpy == LABEL_CHAR || (*cpy >= '0' && *cpy <= '9') || *cpy == DIRECT_CHAR || *cpy == '-')
			if (check_other_arguments(cpy))
				error_argument_overflow(line);
		while (*cpy && *cpy != SEPARATOR_CHAR)
			cpy++;
		if (*cpy)
			cpy++;
	}
}

void	validate_overflow(t_asm_list *list)
{
	int			line;

	line = 3;
	while (list)
	{
		if (list->command->is_label)
		{
			line++;
			list = list->next;
			continue ;
		}
		else
			validate_numbers(list->command, line);
		list = list->next;
		line++;
	}
}