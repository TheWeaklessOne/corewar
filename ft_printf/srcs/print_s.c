/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoughnu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 10:03:42 by sdoughnu          #+#    #+#             */
/*   Updated: 2019/10/24 10:03:43 by sdoughnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_prcn_s(t_flags *yep)
{
	int	len;

	len = ft_strlen(yep->s);
	if (yep->prcn < len)
		yep->s[yep->prcn] = '\0';
}

static void		ft_width_s(t_flags *yep)
{
	int	len;

	len = ft_strlen(yep->s);
	if (len < yep->width)
	{
		while (yep->min == 1 && len < yep->width)
		{
			yep->s = ft_strjoin(yep->s, " ");
			len++;
		}
		while (yep->zero == 1 && len < yep->width)
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

size_t			ft_s(t_flags *yep, char *s)
{
	size_t	res;

	if (s)
		yep->s = ft_strdup(s);
	else
		yep->s = ft_strdup("(null)");
	if (yep->prcn >= 0)
		ft_prcn_s(yep);
	if (yep->width > 0)
		ft_width_s(yep);
	res = ft_putstr(yep->s);
	return (res);
}
