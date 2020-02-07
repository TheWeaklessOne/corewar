/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_di.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoughnu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 13:38:49 by sdoughnu          #+#    #+#             */
/*   Updated: 2019/10/26 17:47:39 by sdoughnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_neg(t_flags *yep)
{
	char *buf;

	if (*(yep->s) != '-')
		return (0);
	buf = yep->s;
	(yep->s)++;
	if (!(yep->s = ft_strdup(yep->s)))
		return (-2);
	free(buf);
	return (1);
}

static void		ft_prcn(t_flags *yep)
{
	int		len;
	char	*tmp;

	len = ft_strlen(yep->s);
	if (yep->prcn > len)
	{
		while (len++ < yep->prcn)
		{
			tmp = yep->s;
			yep->s = ft_strjoin("0", tmp);
			free(tmp);
		}
	}
}

static void		ft_addflag(t_flags *yep, int sign)
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

static void		ft_width_di(int sign, t_flags *yep)
{
	int		len;
	char	*tmp;

	len = ft_strlen(yep->s);
	while (yep->min == 1 && yep->width > len++ && (tmp = yep->s))
	{
		yep->s = ft_strjoin(tmp, " ");
		free(tmp);
	}
	if (yep->zero == 1 && yep->min == 0 && (yep->plus == 1 || sign == 1
	|| yep->space == 1) && yep->prcn < 0)
		len++;
	while (yep->zero == 1 && yep->prcn < 0 && len++ < yep->width)
	{
		tmp = yep->s;
		yep->s = ft_strjoin("0", tmp);
		free(tmp);
	}
	while (len++ < yep->width && (tmp = yep->s))
	{
		yep->s = ft_strjoin(" ", tmp);
		free(tmp);
	}
}

size_t			ft_arg_di(t_flags *yep)
{
	size_t	res;
	int		sign;
	int		num;

	num = 0;
	if (*(yep->s) == '0' && *(yep->s + 1) == '\0')
		num++;
	if ((sign = ft_neg(yep)) == -2)
		return (-2);
	ft_prcn(yep);
	if (num == 1 && yep->prcn == 0)
	{
		free(yep->s);
		yep->s = ft_strdup("");
	}
	if (yep->zero != 1 || yep->min == 1 || yep->prcn >= 0)
		ft_addflag(yep, sign);
	ft_width_di(sign, yep);
	if (yep->zero == 1 && yep->min != 1 && yep->prcn < 0)
		ft_addflag(yep, sign);
	res = ft_putstr(yep->s);
	return (res);
}
