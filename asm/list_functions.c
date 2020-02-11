/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stross <stross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 14:56:13 by stross            #+#    #+#             */
/*   Updated: 2020/02/07 13:11:59 by stross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_asm_list	*ft_create_elem(t_command *command)
{
	t_asm_list	*list;

	list = (t_asm_list*)ft_memalloc(sizeof(t_asm_list));
	list->command = command;
	return (list);
}

void				ft_list_push_back(t_asm_list **begin_list, t_command *command)
{
	t_asm_list	*list;

	if (begin_list)
	{
		if (*begin_list == NULL)
			*begin_list = ft_create_elem(command);
		else
		{
			list = (*begin_list);
			while (list->next)
				list = list->next;
			list->next = ft_create_elem(command);
		}
	}
}

void				ft_list_clear(t_asm_list **begin_list)
{
	if (*begin_list && (*begin_list)->next)
	{
		ft_list_clear(&(*begin_list)->next);
	}
	if (*begin_list)
		free(*begin_list);
	*begin_list = NULL;
}