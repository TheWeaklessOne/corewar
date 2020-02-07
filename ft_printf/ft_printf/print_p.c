/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoughnu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:33:51 by sdoughnu          #+#    #+#             */
/*   Updated: 2019/10/23 16:33:54 by sdoughnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_width_p(t_flags *yep)
{
	int			len;
	char		*tmp;

	len = ft_strlen(yep->s);
	if (yep->width > len)
	{
		while (yep->min != 0 && len++ < yep->width && (tmp = yep->s))
		{
			yep->s = ft_strjoin(tmp, " ");
			free(tmp);
		}
		if (yep->zero != 0 && yep->min == 0)
			len += 2;
		while (yep->zero != 0 && len++ < yep->width && (tmp = yep->s))
		{
			yep->s = ft_strjoin("0", tmp);
			free(tmp);
		}
		while (len++ < yep->width && (tmp = yep->s))
		{
			yep->s = ft_strjoin(" ", tmp);
			free(tmp);
		}
	}
}

static void		ft_prcn_p(t_flags *yep)
{
	int			len;
	char		*tmp;

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
	if (yep->prcn == 0 && *(yep->s) == '0' && *(yep->s + 1) == '\0')
	{
		free(yep->s);
		yep->s = ft_strdup("");
	}
}

size_t			ft_p(t_flags *yep, void *tmp)
{
	long long	buf;
	size_t		res;
	char		*tmpp;

	buf = (unsigned long long)tmp;
	yep->s = ft_itoa_base(buf, 16, 'a');
	ft_prcn_p(yep);
	if (yep->zero != 0 && yep->min == 0)
		ft_width_p(yep);
	tmpp = yep->s;
	yep->s = ft_strjoin("0x", tmpp);
	free(tmpp);
	ft_width_p(yep);
	res = ft_putstr(yep->s);
	return (res);
}
