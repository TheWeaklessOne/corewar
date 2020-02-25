/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stross <stross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 18:49:17 by stross            #+#    #+#             */
/*   Updated: 2020/02/25 16:17:32 by stross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	*get_name(char *filename)
{
	char	**split;
	char	*ret;
	int		i;

	i = 0;
	split = ft_strsplit(filename, '/');
	while (split[i + 1])
		i++;
	ret = ft_strdup(split[i]);
	free_split(split);
	return (ret);
}

static char	*get_new_ext(char *filename, int *mod)
{
	int		i;
	char	*f_name;

	i = 0;
	f_name = NULL;
	filename = get_name(filename);
	while (filename[i] && filename[i] != '.')
		i++;
	if (ft_strequ(filename + i, ".s"))
	{
		*mod = ASM;
		if (!(f_name = (char*)ft_memalloc(i + 5)))
			error_allocation();
		ft_strncpy(f_name, filename, ++i);
		ft_strncpy(f_name + i, "cor", 3);
	}
	else if (ft_strequ(filename + i, ".cor"))
		norm_get_ext(mod, &f_name, i, &filename);
	else
		error_usage();
	free(filename);
	return (f_name);
}

static char	*file_ext_with_dir(char *filename)
{
	char	*new;
	char	*temp;
	char	*temp2;

	temp = ft_strdup(filename);
	temp2 = ft_strrchr(temp, '.');
	if (temp2 != NULL)
	{
		*temp2 = '\0';
		new = ft_strjoin(temp, ".cor");
	}
	else
		exit(1);
	free(temp);
	return (new);
}

static void	help_write_path(char *dir_path)
{
	write(1, "Writing output program to ", 26);
	write(1, dir_path, ft_strlen(dir_path));
	write(1, "\n", 1);
}

void		create_file(char **argv, t_head *head)
{
	char	*new_fn;
	char	*dir_path;
	char	*filename;
	int		fd;
	int		mod;

	filename = argv[1];
	new_fn = get_new_ext(filename, &mod);
	dir_path = file_ext_with_dir(filename);
	if (mod != ASM)
		diss_not_ready();
	if (mod == ASM)
		validator(argv, head);
	if ((fd = open(dir_path, O_WRONLY | O_CREAT, 0644)) == -1)
	{
		write(2, "Failed to create file\n", 22);
		exit(1);
	}
	help_write_path(dir_path);
	free(new_fn);
	free(dir_path);
	if (mod == ASM)
		assembly(fd, head);
	else
		exit(1);
}
