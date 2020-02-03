/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoye <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 21:42:20 by djoye             #+#    #+#             */
/*   Updated: 2019/09/10 21:59:24 by djoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *lst;
	t_list *nlist;

	lst = *alst;
	while (lst)
	{
		nlist = lst->next;
		del(lst->content, lst->content_size);
		free(lst);
		lst = nlist;
	}
	*alst = NULL;
}
