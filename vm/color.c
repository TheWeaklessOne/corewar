/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoughnu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 19:58:36 by sdoughnu          #+#    #+#             */
/*   Updated: 2020/02/16 19:58:37 by sdoughnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int 		print_fd(const char *s, int fd)
{
	write(fd, "\033[31m", 5);
	write(fd, s, ft_strlen(s));
	write(fd, "\033[0m", 4);
	return (0);
}

int 		error_in(const char *s1, const char *s2, int fd)
{
	write(fd, "\033[31m", 5);
	write(fd, s1, ft_strlen(s1));
	write(fd, s2, ft_strlen(s2));
	write(fd, "\033[0m", 4);
	write(fd, "\n", 1);
	return (0);
}
