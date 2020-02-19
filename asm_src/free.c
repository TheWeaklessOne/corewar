/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stross <stross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 20:26:20 by stross            #+#    #+#             */
/*   Updated: 2020/02/18 11:48:42 by stross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	free_head(t_head *head)
{
	int		i;

	i = 0;
	while (head->commands[i])
	{
		if (head->commands[i]->label)
			free(head->commands[i]->label);
//		if (head->commands[i]->command)
//			free(head->commands[i]->command);
		free(head->commands[i]);
		i++;
	}
	if (head->commands)
		free(head->commands);
	free(head);
}

void	free_split(char **arr)
{
	unsigned int	x;

	x = 0;
	while (arr[x])
	{
		free(arr[x]);
		x++;
	}
	free(arr);
}