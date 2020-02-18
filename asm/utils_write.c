/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_write.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stross <stross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 18:19:51 by stross            #+#    #+#             */
/*   Updated: 2020/02/13 16:58:45 by stross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		write_exec_code_2b(int size, int fd)
{
	t_4bytes		num;
	unsigned char	octet;

	num.hex = size;
	if (num.field.octet2 == 0)
		write(fd, "\0", 1);
	else
	{
		octet = num.field.octet2;
		write(fd, &octet, 1);
	}
	if (num.field.octet1 == 0)
		write(fd, "\0", 1);
	else
	{
		octet = num.field.octet1;
		write(fd, &octet, 1);
	}
}

void		main_write(int fd, t_command *command, t_command **commands, int mod)
{
	char	*str;
	int		i;

	i = 0;
	str = command->command + ft_strlen(g_op[command->name -1]);
	while (i < 3)
	{
		while (ft_isspace(*str))
			str++;
		if (*str == 'r')
			write_reg(fd, str);
		else if ((*str == DIRECT_CHAR && mod == 2) || *str == LABEL_CHAR || (*str >= '0' && *str <= '9') || *str == '-')
			handle_dir_2size(fd, str, command, commands);
		else if (*str == DIRECT_CHAR && mod == 4)
			handle_dir(fd, str, command, commands);
		if (i < 2)
		{
			while (*str && *str != SEPARATOR_CHAR)
				str++;
		}
		if (*str)
			str++;
		i++;
	}
}

static void	write_arg_type_help(t_one_byte *octet, unsigned char *arr, int *i)
{
	*i = -1;
	octet->num = 0;
	ft_bzero(arr, 3 * sizeof(char));
}

void		write_arg_type(char *str, int fd, int mod)
{
	t_one_byte		octet;
	int				i;
	unsigned char	arr[3];

	write_arg_type_help(&octet, arr, &i);
	str += ft_strlen(g_op[mod - 1]);
	while (i++ != 3)
	{
		while (ft_isspace(*str))
			str++;
		if (*str == LABEL_CHAR || (*str >= '0' && *str <= '9') || *str == '-')
			arr[i] = 3;
		else if (*str == 'r')
			arr[i] = 1;
		else if (*str == DIRECT_CHAR)
			arr[i] = 2;
		while (*str && *str != SEPARATOR_CHAR)
			str++;
		if (*str)
			str++;
	}
	octet.field.dt = arr[0];
	octet.field.ct = arr[1];
	octet.field.bt = arr[2];
	write(fd, &octet.num, 1);
}

char		*get_comm_label(char *str)
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