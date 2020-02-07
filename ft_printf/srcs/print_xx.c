/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_xx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoughnu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 14:11:49 by sdoughnu          #+#    #+#             */
/*   Updated: 2019/10/27 14:11:55 by sdoughnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_x2(t_flags *yep, va_list *ap, int flag)
{
	unsigned short	h;
	unsigned char	hh;
	unsigned		i;

	if (yep->len == 3)
	{
		h = (unsigned short)va_arg(*ap, int);
		i = (unsigned int)h;
		yep->s = ft_itoa_base_u(i, 16, (flag > 0) ? 'a' : 'A');
	}
	else if (yep->len == 4)
	{
		hh = (unsigned char)va_arg(*ap, int);
		i = (unsigned int)hh;
		yep->s = ft_itoa_base_u(i, 16, (flag > 0) ? 'a' : 'A');
	}
}

size_t			ft_x(t_flags *yep, va_list *ap)
{
	int					flag;
	unsigned int		i;
	unsigned long		l;
	unsigned long long	ll;

	flag = (*(yep->type) == 'x') ? 1 : -1;
	if (yep->len == 0)
	{
		i = (unsigned int)va_arg(*ap, unsigned int);
		yep->s = ft_itoa_base_u(i, 16, (flag > 0) ? 'a' : 'A');
	}
	else if (yep->len == 1)
	{
		l = (unsigned long)va_arg(*ap, unsigned long);
		yep->s = ft_itoa_base_u(l, 16, (flag > 0) ? 'a' : 'A');
	}
	else if (yep->len == 2)
	{
		ll = (unsigned long long)va_arg(*ap, unsigned long long);
		yep->s = ft_itoa_base_u(ll, 16, (flag > 0) ? 'a' : 'A');
	}
	else
		ft_x2(yep, ap, flag);
	return (ft_arg_x(yep, flag));
}
