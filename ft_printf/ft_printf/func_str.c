/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoughnu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 12:07:02 by sdoughnu          #+#    #+#             */
/*   Updated: 2019/10/22 12:07:07 by sdoughnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long int	ft_atoi(const char *str)
{
	int					sign;
	unsigned long int	nbr;

	sign = 1;
	nbr = 0;
	while (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\v' ||
	*str == '\f' || *str == '\r')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str += 1;
	}
	while (*str >= '0' && *str <= '9')
	{
		nbr = (nbr * 10) + (*str - '0');
		str += 1;
	}
	return ((long int)nbr * sign);
}

size_t		ft_putstr(const char *s)
{
	size_t i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}

size_t		ft_strlen(char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int			ft_strcmp(const char *s1, const char *s2)
{
	unsigned int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}
