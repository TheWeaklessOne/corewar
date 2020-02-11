/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_write.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stross <stross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 18:19:51 by stross            #+#    #+#             */
/*   Updated: 2020/02/11 14:38:37 by stross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	write_arg_type()

char	*get_comm_label(char *str)
{
	int		i;
	char	*ret;
	char	*temp;

	i = 0;
	if (*str == LABEL_CHAR)
		str++;
	while (str[i] && str[i] != ' ' && str[i] != SEPARATOR_CHAR && str[i] != '\t')
		i++;
	ret = (char*)ft_memalloc(i + 1);
	temp = ret;
	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != SEPARATOR_CHAR && str[i] != '\t')
		*ret++ = *str++;
	return (temp);
}