/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoye <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 19:05:44 by djoye             #+#    #+#             */
/*   Updated: 2019/10/28 19:07:10 by djoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char					*ft_itoa_base(long long dig, int base, char a)
{
	char				*s;
	int					i;
	unsigned long long	nb;
	int					res;
	int					sgn;

	sgn = (dig >= 0) ? 1 : -1;
	i = (dig < 0 && base == 10) || dig == 0 ? 1 : 0;
	dig = (sgn >= 0) ? dig : -dig;
	nb = dig;
	while (dig && ++i && base > 1 && base <= 36)
		dig = dig / base;
	if (!(s = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	s[i--] = '\0';
	s[0] = sgn < 0 && base == 10 ? '-' : '0';
	while (base > 1 && base <= 36 && nb)
	{
		res = nb % base;
		s[i--] = res <= 9 ? res + '0' : res + a - 10;
		nb = nb / base;
	}
	return (s);
}

static void				ft_float_help(long double *nb, long *i,
		long *acc, int *sgn)
{
	*nb = (*nb < 0) ? -(*nb) : *nb;
	*i = 0;
	while (*i < *acc)
	{
		(*nb) = (*nb) * 10;
		(*i)++;
	}
	*nb = *nb + 0.5;
	while (*i)
	{
		(*i)--;
		*nb /= 10;
	}
	*i = (*acc > 0) ? 1 : 0;
	*i += (*sgn == 1) ? 1 : 0;
}

char					*ft_float(long double nb, long acc)
{
	char				*num;
	long				i;
	int					sgn;
	long double			ld;
	char				*res;

	sgn = ((*(__int128_t*)&nb) >> 79) & 1;
	ft_float_help(&nb, &i, &acc, &sgn);
	ld = nb;
	while (ld > 1 && ++i)
		ld = ld / 10;
	res = (char*)malloc(sizeof(char) * (i + acc + 2));
	num = ft_itoa_base((unsigned long long int)nb, 10, 'A');
	i = 0;
	res[0] = (sgn == 1 && ++i) ? '-' : '0';
	while (*num != '\0')
		res[i++] = *num++;
	free(num - (i - sgn));
	res[i] = (acc != 0) ? '.' : '\0';
	while (acc-- > 0 && (nb = nb * 10) >= 0 && ++i)
		if ((res[i] = ((unsigned long long)nb % 10 + '0')))
			nb = nb - (unsigned long long)nb;
	res[++i] = '\0';
	return (res);
}
