/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmuller <fmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 19:24:19 by vinvimo           #+#    #+#             */
/*   Updated: 2018/03/21 20:04:55 by fmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <wchar.h>

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

int					ft_atoi(const char *str);
void				ft_bzero(void *s, size_t n);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strchr(const char *s, int c);
void				ft_strclr(char *s);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strcpy_c(char *dst, const char *src, char *end);
void				ft_strdel(char **as);
char				*ft_strdup(const char *s1);
int					ft_strequ(char const *s1, char const *s2);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strjoin(char const *s1, const char *s2);
char				*ft_strjoin_char(char const *s1, char const *s2, char c);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlen(char const *str);
size_t				ft_strlen_c(const char *s, char *end);
size_t				ft_strlen_w(const wchar_t *s);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strncat(char *s1, const char *s2, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strncpy(char *dst, const char *src, size_t n);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strnew(size_t size);
wchar_t				*ft_strnew_w(size_t size);
char				*ft_strnstr(const char *s1, const char *s2, size_t n);
char				*ft_strrchr(const char *s, int c);
char				**ft_strsplit(char const *s, char c);
char				*ft_strstr(const char *s1, const char *s2);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strtrim(char const *s);
long double			ft_sqrt(long double nb);
void				ft_swap(int *a, int *b);
char				*ft_itoa(int n);
void				*ft_memalloc(size_t size);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				ft_memdel(void **ap);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memset_w(void *b, int c, size_t len);
void				ft_putchar(char c);
void				ft_putchar_w(wchar_t c);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl(char const *s);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr(int n);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr(char const *s);
void				ft_putstr_w(wchar_t const *s);
void				ft_putstr_fd(char const *s, int fd);
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
int					ft_is_end(char c, char *end);

t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list				*ft_lstnew(void const *content, size_t content_size);

int					get_next_line(const int fd, char **line);

/*
** maths functions
*/

long double			pi_gauss_legendre(long double pi, int precision);
long double			ft_power(long double x, int y);

/*
** FMuller functions
*/

typedef struct		s_pbit
{
	void			*ptr;
	size_t			n;
}					t_pbit;

int					ft_printf(const char *format, ...);
int					ft_printf_fd(int fd, const char *format, ...);

void				ft_tabc_del(char ***tab);
char				*ft_str_insert(char **dst, char *src, size_t index,
																size_t dst_len);
int					ft_wc_size(wchar_t c);
wchar_t				*ft_wc_strsub(wchar_t const *s, unsigned int start,
																	size_t len);
void				ft_wc_to_cs(char *dest, wchar_t src);
int					ft_wcs_to_cs(char **dest, const wchar_t *src);
wchar_t				*ft_wc_strncpy(wchar_t *dst, const wchar_t *src,
																	size_t len);
int					ft_wcs_conv_len(const wchar_t *s);
size_t				ft_wcslen(const wchar_t *s);
char				*ft_itoa_base(long long n, int base);
char				*ft_unsigned_itoa_base(unsigned long long n, int base);
void				ft_init_pbit(t_pbit *pbit, void *ptr, size_t n);
void				ft_ncpy_bit(t_pbit src, t_pbit dst, size_t len);
int					ft_read_bit(void *ptr, size_t n);
void				ft_set_bit(void *ptr, int value, size_t n);
int					ft_iswhitespace(int c);
int					*ft_nbdup(int lenght, ...);
int					*ft_nbcpy(int *tab, int lenght, ...);
void				*ft_realloc(void *ptr, size_t size);

#endif
