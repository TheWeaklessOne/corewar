/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_f.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoughnu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 13:10:43 by sdoughnu          #+#    #+#             */
/*   Updated: 2019/10/25 13:10:44 by sdoughnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_neg(t_flags *yep, int flag)
{
	char	*buf;

	if (*(yep->s) != '-')
		return (0);
	if (yep->zero != 0 && flag == 1)
		return (1);
	buf = yep->s;
	yep->s++;
	if (!(yep->s = ft_strdup(yep->s)))
		return (-2);
	free(buf);
	return (1);
}

static void		ft_flag_f(t_flags *yep, int sign)
{
	char *tmp;

	if (sign == 0)
	{
		if (yep->space == 1 && yep->plus == 0)
		{
			tmp = yep->s;
			yep->s = ft_strjoin(" ", tmp);
			free(tmp);
		}
		else if (yep->plus == 1)
		{
			tmp = yep->s;
			yep->s = ft_strjoin("+", tmp);
			free(tmp);
		}
	}
	else
	{
		tmp = yep->s;
		yep->s = ft_strjoin("-", tmp);
		free(tmp);
	}
}

static void		ft_width_f(t_flags *yep, int sign, int flag)
{
	int		len;
	char	*tmp;

	len = ft_strlen(yep->s);
	while (yep->min == 1 && yep->width > len++)
	{
		tmp = yep->s;
		yep->s = ft_strjoin(tmp, " ");
		free(tmp);
	}
	if (yep->zero == 1 && yep->min == 0 && (yep->plus == 1
	|| yep->space == 1 || sign == 1) && flag != 1)
		len++;
	while (yep->zero == 1 && flag != 1 && len++ < yep->width)
	{
		tmp = yep->s;
		yep->s = ft_strjoin("0", tmp);
		free(tmp);
	}
	while (len++ < yep->width)
	{
		tmp = yep->s;
		yep->s = ft_strjoin(" ", tmp);
		free(tmp);
	}
}

static void		ft_width_flag(t_flags *yep)
{
	int len;

	len = ft_strlen(yep->s);
	if (yep->width > len)
	{
		while (yep->min == 1 && yep->width > len)
		{
			yep->s = ft_strjoin(yep->s, " ");
			len++;
		}
		while (len < yep->width)
		{
			yep->s = ft_strjoin(" ", yep->s);
			len++;
		}
	}
}

size_t			ft_arg_f(t_flags *yep, int flag)
{
	size_t	res;
	int		sign;

	if (flag == 0 || flag == 1)
	{
		if ((sign = ft_neg(yep, flag)) == -2)
			return (-2);
		if (yep->zero == 0 || yep->min == 1 || (yep->zero == 1 &&
		flag == 1 && sign != 1))
			ft_flag_f(yep, sign);
		ft_width_f(yep, sign, flag);
		if (yep->zero == 1 && yep->min != 1 && flag != 1)
			ft_flag_f(yep, sign);
	}
	else if (flag == 2)
		ft_width_flag(yep);
	res = ft_putstr(yep->s);
	return (res);
}
