/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoughnu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 12:07:53 by sdoughnu          #+#    #+#             */
/*   Updated: 2019/10/22 12:07:56 by sdoughnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_flags(t_flags *yep, char **str)
{
	while (**str && (**str == ' ' || **str == '-' || **str == '+' ||
	**str == '0' || **str == '#'))
	{
		(**str == '-') ? yep->min = 1 : 0;
		(**str == '+') ? yep->plus = 1 : 0;
		(**str == ' ') ? yep->space = 1 : 0;
		(**str == '0') ? yep->zero = 1 : 0;
		(**str == '#') ? yep->hash = 1 : 0;
		(*str)++;
	}
	if (yep->space == 1 && yep->plus == 1)
		yep->space = 0;
	if (yep->zero == 1 && yep->min == 1)
		yep->zero = 0;
}

static void		ft_width(t_flags *yep, char **str, va_list *ap)
{
	if (**str == '*')
	{
		yep->width = (long int)va_arg(*ap, int);
		if (yep->width < 0)
		{
			yep->width = yep->width * (-1);
			yep->min = 1;
		}
		(*str)++;
	}
	else
	{
		yep->width = ft_atoi(*str);
		while (**str && **str >= '0' && **str <= '9')
			(*str)++;
	}
}

static int		ft_precis(t_flags *yep, char **str, va_list *ap)
{
	if (**str && (**str >= '0' && **str <= '9'))
		yep->prcn = ft_atoi(*str);
	else if (**str == '*')
	{
		yep->prcn = (long int)va_arg(*ap, int);
		if (yep->prcn < 0)
			yep->prcn = -1;
		*str += 1;
	}
	else if (**str == '-')
		yep->prcn = -2;
	else if (**str == '\0')
		return (-1);
	else
		yep->prcn = 0;
	while (**str && **str >= '0' && **str <= '9')
		*str += 1;
	return (1);
}

static void		ft_long(t_flags *yep, char **str)
{
	if (**str == 'l')
	{
		yep->len = 1;
		*str += 1;
	}
	else if (**str == 'h')
	{
		yep->len = 3;
		*str += 1;
	}
	else if (**str == 'L')
	{
		yep->len = 5;
		*str += 1;
	}
	if (**str == 'l' && yep->len == 1)
	{
		yep->len = 2;
		*str += 1;
	}
	if (**str == 'h' && yep->len == 3)
	{
		yep->len = 4;
		*str += 1;
	}
}

int				ft_parse(t_flags *yep, va_list *ap, char *str)
{
	ft_flags(yep, &str);
	ft_width(yep, &str, ap);
	if (*str == '*' || (*str >= '0' && *str <= '9'))
		ft_width(yep, &str, ap);
	if (*str == '.')
	{
		str += 1;
		if ((ft_precis(yep, &str, ap)) == -1)
			return (-1);
	}
	ft_long(yep, &str);
	while (*str && (*str == '0' || *str == '-' || *str == '#' ||
	*str == ' ' || *str == '+'))
		ft_flags(yep, &str);
	yep->type = str;
	return (1);
}
