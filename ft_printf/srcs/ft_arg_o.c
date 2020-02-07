/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_o.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoughnu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 12:31:10 by sdoughnu          #+#    #+#             */
/*   Updated: 2019/10/23 12:31:12 by sdoughnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_hash_o(t_flags *yep, int num)
{
	char *tmp;

	if (yep->hash != 0 && num != 1)
	{
		tmp = yep->s;
		yep->s = ft_strjoin("0", tmp);
		free(tmp);
	}
}

static void		ft_width_o(t_flags *yep)
{
	int		len;
	char	*tmp;

	len = ft_strlen(yep->s);
	if (yep->width > len)
	{
		while (yep->min != 0 && len++ < yep->width)
		{
			tmp = yep->s;
			yep->s = ft_strjoin(tmp, " ");
			free(tmp);
		}
		while (yep->prcn < 0 && yep->zero != 0 && len++ < yep->width)
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

static void		ft_prcn_o(t_flags *yep)
{
	int		num;
	int		len;
	char	*tmp;

	num = 0;
	if (*(yep->s) == '0' && (*(yep->s + 1)) == '\0')
		num++;
	ft_hash_o(yep, num);
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
	if (num == 1 && yep->prcn == 0 && yep->hash != 1)
	{
		free(yep->s);
		yep->s = ft_strdup("");
	}
	ft_width_o(yep);
}

size_t			ft_arg_o(t_flags *yep)
{
	size_t res;

	ft_prcn_o(yep);
	res = ft_putstr(yep->s);
	return (res);
}
