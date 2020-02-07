/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_assoc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoughnu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 14:10:58 by sdoughnu          #+#    #+#             */
/*   Updated: 2019/10/26 17:31:59 by sdoughnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t		ft_assoc(va_list *ap, t_flags *yep)
{
	size_t	res;

	if (*(yep->type) == 'd' || *(yep->type) == 'i' || *(yep->type) == 'D'
			|| *(yep->type) == 'I')
		res = ft_di(yep, ap);
	else if (*(yep->type) == 'o' || *(yep->type) == 'O')
		res = ft_o(yep, ap);
	else if (*(yep->type) == 'u' || *(yep->type) == 'U')
		res = ft_u(yep, ap);
	else if (*(yep->type) == 'x' || *(yep->type) == 'X')
		res = ft_x(yep, ap);
	else if (*(yep->type) == 'c')
		res = ft_c(yep, (char)va_arg(*ap, int));
	else if (*(yep->type) == 's')
		res = ft_s(yep, (char *)va_arg(*ap, char *));
	else if (*(yep->type) == 'p')
		res = ft_p(yep, va_arg(*ap, void *));
	else if (*(yep->type) == 'f')
		res = ft_f(yep, ap);
	else if (*(yep->type) == '%')
		res = ft_perc(yep);
	else
		res = ft_c(yep, *(yep->type));
	ft_delete(yep);
	return (res);
}
