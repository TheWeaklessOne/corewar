/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoughnu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 12:52:11 by sdoughnu          #+#    #+#             */
/*   Updated: 2019/10/25 12:52:12 by sdoughnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_error(long double nb)
{
	if (nb != nb)
		return (1);
	else if (nb == 1.0 / 0.0)
		return (2);
	else if (nb == -1.0 / 0.0)
		return (3);
	return (0);
}

size_t			ft_f(t_flags *yep, va_list *ap)
{
	int			flag;
	int			ret;
	long double	ld;

	yep->prcn == -1 ? yep->prcn = 6 : yep->prcn;
	yep->prcn == -2 ? yep->prcn = 0 : yep->prcn;
	if (yep->len == 5)
		ld = (long double)va_arg(*ap, long double);
	else
		ld = (double)va_arg(*ap, double);
	ret = ft_error(ld);
	if (ret == 0)
		yep->s = ft_float(ld, yep->prcn);
	else if (ret == 1)
		yep->s = ft_strdup("nan");
	else if (ret == 2)
		yep->s = ft_strdup("inf");
	else if (ret == 3)
		yep->s = ft_strdup("-inf");
	flag = (ret == 2 || ret == 3) ? 1 : 0;
	flag = (ret == 1) ? 2 : flag;
	if (flag == 0)
		if (yep->hash == 1 && yep->prcn == 0)
			yep->s = ft_strjoin(yep->s, ".");
	return (ft_arg_f(yep, flag));
}
