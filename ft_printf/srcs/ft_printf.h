/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdoughnu <sdoughnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 14:02:01 by sdoughnu          #+#    #+#             */
/*   Updated: 2019/10/28 18:32:42 by djoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <wchar.h>
# include <string.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>

typedef struct	s_list
{
	int			plus;
	int			min;
	int			space;
	int			hash;
	int			zero;
	long int	width;
	long int	prcn;
	char		*type;
	int			len;
	char		*s;
}				t_flags;

int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strdup(const char *s1);
char			*ft_strnew(size_t size);
size_t			ft_strlen(char *str);
size_t			ft_putstr(const char *s);

char			*ft_itoa_base_u(unsigned long long dig, int base, char a);
char			*ft_itoa_base(long long dig, int base, char a);

char			*ft_float(long double nb, long acc);
size_t			ft_arg_f(t_flags *yep, int flag);
size_t			ft_f(t_flags *yep, va_list *ap);

void			ft_delete(t_flags *yep);

size_t			ft_s(t_flags *yep, char *s);
size_t			ft_c(t_flags *yep, char c);
size_t			ft_perc(t_flags *yep);

size_t			ft_p(t_flags *yep, void *tmp);
size_t			ft_u(t_flags *yep, va_list *ap);

size_t			ft_arg_o(t_flags *yep);
size_t			ft_o(t_flags *yep, va_list *ap);

size_t			ft_arg_x(t_flags *yep, int flag);
size_t			ft_x(t_flags *yep, va_list *ap);

size_t			ft_arg_di(t_flags *yep);
size_t			ft_di(t_flags *yep, va_list *ap);

size_t			ft_assoc(va_list *ap, t_flags *yep);

long int		ft_atoi(const char *str);
int				ft_parse(t_flags *yep, va_list *ap, char *str);
size_t			ft_treatment(va_list *ap, char **format, t_flags *yep);

void			ft_putstrl(char *str, int len);
int				ft_parsestr(const char *format, va_list *ap);
int				ft_printf(const char *format, ...);

#endif
