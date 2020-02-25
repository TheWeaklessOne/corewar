/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoye <djoye@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 13:57:57 by djoye             #+#    #+#             */
/*   Updated: 2020/02/25 17:19:05 by djoye            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <wchar.h>
# include <string.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <string.h>
# include <ctype.h>
# include <stdio.h>

typedef struct		s_list
{
	int				plus;
	int				min;
	int				space;
	int				hash;
	int				zero;
	long int		width;
	long int		prcn;
	char			*type;
	int				len;
	char			*s;
}					t_flags;

void				*ft_memset(void *b, int c, size_t len);
void				*ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s1);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *haystack, const char *needle, \
		size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char(*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
char				*ft_strcapitalize(char *str);
char				*ft_strlowcase(char *str);
char				*ft_strupcase(char *str);
int					ft_str_is_alpha(char *str);
int					ft_str_is_numeric(char *str);

char				*ft_itoa_base_u(unsigned long long dig, int base, char a);
char				*ft_itoa_base(long long dig, int base, char a);

char				*ft_float(long double nb, long acc);
size_t				ft_arg_f(t_flags *yep, int flag);
size_t				ft_f(t_flags *yep, va_list *ap);

void				ft_delete(t_flags *yep);

size_t				ft_s(t_flags *yep, char *s);
size_t				ft_c(t_flags *yep, char c);
size_t				ft_perc(t_flags *yep);

size_t				ft_p(t_flags *yep, void *tmp);
size_t				ft_u(t_flags *yep, va_list *ap);

size_t				ft_arg_o(t_flags *yep);
size_t				ft_o(t_flags *yep, va_list *ap);

size_t				ft_arg_x(t_flags *yep, int flag);
size_t				ft_x(t_flags *yep, va_list *ap);

size_t				ft_arg_di(t_flags *yep);
size_t				ft_di(t_flags *yep, va_list *ap);

size_t				ft_assoc(va_list *ap, t_flags *yep);

int					ft_parse(t_flags *yep, va_list *ap, char *str);
size_t				ft_treatment(va_list *ap, char **format, t_flags *yep);

void				ft_putstrl(char *str, int len);
int					ft_parsestr(const char *format, va_list *ap);
int					ft_printf(const char *format, ...);

#endif
