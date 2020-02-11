/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stross <stross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 18:49:17 by stross            #+#    #+#             */
/*   Updated: 2020/02/10 14:46:26 by stross           ###   ########.fr       */
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
		if(!(f_name = (char*)ft_memalloc(i + 5)))
			error_allocation();
		ft_strncpy(f_name, filename, ++i);
		ft_strncpy(f_name + i, "cor", 3);
	}
	else if (ft_strequ(filename + i, ".cor"))
	{
		*mod = DISASM;
		if(!(f_name = (char*)ft_memalloc(i + 3)))
			error_allocation();
		ft_strncpy(f_name, filename, ++i);
		ft_strncpy(f_name + i, "s", 1);
	}
	else
		error_usage();
	free(filename);
	return (f_name);
}

void		create_file(char **argv, t_head *head)
{
	char	*new_fn;
	char	*filename;
	int		fd;
	int		mod;

	filename = argv[1];
	new_fn = get_new_ext(filename, &mod);
	if (mod == ASM)
		validator(argv, head);
	if ((fd = open(new_fn, O_WRONLY | O_CREAT | O_EXCL, 0644)) == -1)
	{
		write(2, "Failed to create file\n", 22);
		exit(1);
	}
	write(1, "Writing output program to ", 26);
	write(1, new_fn, ft_strlen(new_fn));
	write(1, "\n", 1);
	free(new_fn);
	if (mod == ASM)
		assembly(fd, head);
	else
		exit(1); //TODO disassambly
}