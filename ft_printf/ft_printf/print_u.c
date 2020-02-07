/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoughnu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:08:41 by sdoughnu          #+#    #+#             */
/*   Updated: 2019/10/23 16:08:46 by sdoughnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_width_u(t_flags *yep)
{
	int len;

	len = ft_strlen(yep->s);
	if (yep->width > len)
	{
		while (yep->min != 0 && len < yep->width)
		{
			yep->s = ft_strjoin(yep->s, " ");
			len++;
		}
		while (yep->zero != 0 && yep->prcn < 0 && len < yep->width)
		{
			yep->s = ft_strjoin("0", yep->s);
			len++;
		}
		while (len < yep->width)
		{
			yep->s = ft_strjoin(" ", yep->s);
			len++;
		}
	}
}

static void		ft_prcn_u(t_flags *yep)
{
	int len;

	len = ft_strlen(yep->s);
	if (yep->prcn > len)
	{
		while (len < yep->prcn)
		{
			yep->s = ft_strjoin("0", yep->s);
			len++;
		}
	}
}

static void		ft_u2(t_flags *yep, va_list *ap)
{
	if (yep->len == 2)
		yep->s = ft_itoa_base_u(
				(unsigned long long)va_arg(*ap, unsigned long long), 10, 'a');
	else if (yep->len == 3)
		yep->s = ft_itoa_base_u((unsigned short)va_arg(*ap, unsigned int),
								10, 'a');
	else if (yep->len == 4)
		yep->s = ft_itoa_base_u(
				(unsigned char)va_arg(*ap, unsigned int), 10, 'a');
}

size_t			ft_u(t_flags *yep, va_list *ap)
{
	size_t	res;
	int		num;

	num = 0;
	if (yep->len == 0)
		yep->s = ft_itoa_base_u(
				(unsigned int)va_arg(*ap, unsigned int), 10, 'a');
	else if (yep->len == 1)
		yep->s = ft_itoa_base_u(
				(unsigned long)va_arg(*ap, unsigned long), 10, 'a');
	else
		ft_u2(yep, ap);
	if (*(yep->s) == '0' && *(yep->s + 1) == '\0')
		num++;
	ft_prcn_u(yep);
	if (yep->prcn == 0 && num == 1)
	{
		free(yep->s);
		yep->s = ft_strdup("");
	}
	ft_width_u(yep);
	res = ft_putstr(yep->s);
	return (res);
}
