/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stross <stross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 13:38:54 by stross            #+#    #+#             */
/*   Updated: 2020/01/16 14:37:29 by stross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	write_name(int fd, char **arr)
{
	char	*name;
	int		name_len;
	int		i;

	i = 0;
	name_len = PROG_NAME_LENGTH;
	while (arr[i])
	{
		if ((name = ft_strstr(arr[i], ".name")))
			break;
		i++;
	}
	name = ft_strchr(name, '"');
	name++;
	while (name_len && *name && *name != '"')
	{
		write(fd, name, 1);
		name++;
		name_len--;
	}
	while (name_len--)
		write(fd, "\0", 1);
}

void	assembly(int fd, char *str)
{
	int		magic_number;
	char	**arr;

	magic_number = COREWAR_EXEC_MAGIC;
	arr = ft_strsplit(str, '\n');
	write(fd, &magic_number, 4);
	write_name(fd, arr);
//	for (int i = 128; i ; i--)
//	{
//		write(fd, "\0", 1);
//	}
	if ((close(fd)) == -1)
	{
		write(2, "Failed to close file\n", 22);
		exit(1);
	}
	free_split(arr);
}