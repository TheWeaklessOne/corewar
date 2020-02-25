/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stross <stross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 12:47:50 by stross            #+#    #+#             */
/*   Updated: 2020/02/25 16:15:55 by stross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	check_file(char *file, unsigned check)
{
	struct stat		st;
	int				ret;

	if (!file || lstat(file, &st) == -1)
		return (-1);
	ret = 1;
	if (check & IS_L)
		ret &= S_ISLNK(st.st_mode);
	if (check & IS_D)
		ret &= S_ISDIR(st.st_mode);
	if (check & IS_R)
		ret &= ((st.st_mode & S_IRUSR) != 0);
	if (check & IS_W)
		ret &= ((st.st_mode & S_IWUSR) != 0);
	if (check & IS_X)
		ret &= ((st.st_mode & S_IXUSR) != 0);
	return (ret);
}

int			main(int argc, char **argv)
{
	t_head		*head;
	int			ret;

	if (argc != 2)
		error_usage();
	ret = check_file(argv[1], IS_R);
	if (ret == -1)
		write(2, "No such file\n", 13);
	if (ret == 0)
		write(2, "Permission denied\n", 18);
	if (ret == -1 || ret == 0)
		exit(1);
	if (ret == 1)
		if (check_file(argv[1], IS_D) == 1)
		{
			write(2, "It's a directory\n", 17);
			exit(1);
		}
	if (!(head = (t_head*)ft_memalloc(sizeof(t_head))))
		error_allocation();
	create_file(argv, head);
	free_head(head);
	return (0);
}
