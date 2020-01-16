/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stross <stross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:47:32 by stross            #+#    #+#             */
/*   Updated: 2020/01/15 18:23:26 by stross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	get_len(int fd)
{
	int		ret;
	char	buff[BUFF_SIZE];
	ssize_t	nbread;

	ret = 0;
	while ((nbread = read(fd, buff, BUFF_SIZE)))
	{
		if (nbread == -1)
		{
			write(2, "Error while reading a data from a file\n", 40);
			exit(1);
		}
		ret += nbread;
	}
	if ((lseek(fd, 0, SEEK_SET)) == -1)
	{
		write(2, "Error while reading a data from a file\n", 40);
		exit(1);
	}
	return (ret);
}

static void	open_and_close(int *fd, char **argv, char mod)
{
	if (mod == 'o')
	{
		*fd = open(argv[1], O_RDONLY);
		if (*fd == -1)
		{
			write(2, "Failed to open file\n", 21);
			exit(1);
		}
	}
	else if (mod == 'c')
	{
		*fd = close(*fd);
		if (*fd == -1)
		{
			write(2, "Failed to close file\n", 22);
			exit(1);
		}
	}
}

char		*get_string(char **argv)
{
	char	*str;
	int		fd;
	int		len;
	ssize_t	nbread;

	open_and_close(&fd, argv, 'o');
	len = get_len(fd);
	if (!(str = (char*)ft_memalloc(len + 1)))
		error_allocation();
	if ((nbread = read(fd, str, len)) == -1)
	{
		write(2, "Error while reading a data from a file\n", 40);
		exit(1);
	}
	open_and_close(&fd, argv, 'c');
	return (str);
}