/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_perc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoughnu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 17:24:42 by sdoughnu          #+#    #+#             */
/*   Updated: 2019/10/23 17:24:43 by sdoughnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t		ft_perc(t_flags *yep)
{
	int		len;
	size_t	res;

	len = 1;
	yep->s = ft_strdup("%");
	if (len < yep->width)
	{
		while (yep->zero != 0 && len < yep->width)
		{
			yep->s = ft_strjoin("0", yep->s);
			len++;
		}
		while (yep->min != 0 && len < yep->width)
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
	res = ft_putstr(yep->s);
	return (res);
}
