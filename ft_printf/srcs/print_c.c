/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoughnu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 09:27:38 by sdoughnu          #+#    #+#             */
/*   Updated: 2019/10/24 09:27:40 by sdoughnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_width_c(t_flags *yep)
{
	int		len;
	char	*tmp;

	len = ft_strlen(yep->s);
	if (yep->width > len)
	{
		while (yep->min == 1 && len++ < yep->width)
		{
			tmp = yep->s;
			yep->s = ft_strjoin(tmp, " ");
			free(tmp);
		}
		while (yep->zero == 1 && len++ < yep->width)
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
}

size_t			ft_spec_c(t_flags *yep)
{
	size_t		res;
	int			i;

	res = 0;
	i = 0;
	if (yep->min == 1)
		write(1, "\0", 1);
	while (yep->s[i])
	{
		write(1, &(yep->s)[i], 1);
		res++;
		i++;
	}
	if (yep->min != 1)
		write(1, "\0", 1);
	res++;
	return (res);
}

size_t			ft_c(t_flags *yep, char c)
{
	int		num;
	size_t	res;

	num = 0;
	yep->s = ft_strnew(1);
	if (c == 0)
		num++;
	yep->s[0] = c;
	if (num == 1)
		yep->width--;
	if (yep->width > 0)
		ft_width_c(yep);
	if (num == 1)
		res = ft_spec_c(yep);
	else
		res = ft_putstr(yep->s);
	return (res);
}
