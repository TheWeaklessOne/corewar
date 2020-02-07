/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoughnu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 10:53:40 by sdoughnu          #+#    #+#             */
/*   Updated: 2019/10/26 17:32:50 by sdoughnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_delete(t_flags *yep)
{
	yep->plus = 0;
	yep->min = 0;
	yep->space = 0;
	yep->hash = 0;
	yep->zero = 0;
	yep->width = 0;
	yep->prcn = -1;
	yep->len = 0;
	if (yep->s)
	{
		free(yep->s);
		yep->s = NULL;
	}
	yep->type = NULL;
}
