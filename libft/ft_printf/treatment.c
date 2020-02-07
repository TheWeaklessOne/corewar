/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treatment.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoughnu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 12:08:34 by sdoughnu          #+#    #+#             */
/*   Updated: 2019/10/22 12:08:39 by sdoughnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t		ft_treatment(va_list *ap, char **format, t_flags *yep)
{
	yep->plus = 0;
	yep->min = 0;
	yep->space = 0;
	yep->hash = 0;
	yep->zero = 0;
	yep->width = 0;
	yep->prcn = -1;
	yep->len = 0;
	yep->s = NULL;
	yep->type = NULL;
	if (**format == '%')
	{
		(*format)++;
		if (**format != '\0')
		{
			if ((ft_parse(yep, ap, *format)) == -1)
				return (-1);
			*format = yep->type;
			return (ft_assoc(ap, yep));
		}
	}
	return (0);
}
