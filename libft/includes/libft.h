/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evignol <evignol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 15:24:27 by evignol           #+#    #+#             */
/*   Updated: 2016/02/19 13:16:59 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <stdint.h>

# define GREY		"\033[1;30m"
# define RED		"\033[1;31m"
# define GREEN		"\033[1;32m"
# define YELLOW		"\033[1;33m"
# define BLUE		"\033[1;34m"
# define PINK		"\033[1;35m"
# define CYAN		"\033[1;36m"
# define DEFAULT	"\033[00m"

# define PI			3.14159265359f
# define PI2		(PI * 2.f)
# define BUFF_SIZE	32
# define INFINITY	1.0 / 0.0
# define NEG_INF	-1.0 / 0.0

# define FLAG_MINUS		0
# define FLAG_PLUS		1
# define FLAG_SPACE		2
# define FLAG_ZERO		3
# define FLAG_HASHTAG	4

typedef struct		s_calc
{
	int				i;
	int				j;
	int				written;
	double			old;
	double			ent;
	char			tmp[320];
	double			nb;
	int				precision;
}					t_calc;

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_cb
{
	void			*buffer;
	void			*buffer_end;
	size_t			capacity;
	size_t			nb_items;
	size_t			item_size;
	void			*first;
	void			*last;
}					t_cb;

char				cb_init(t_cb *cb, size_t capacity, size_t size);
void				cb_free(t_cb *cb);
char				cb_push_back(t_cb *cb, const void *item);
char				cb_pop_front(t_cb *cb, void *item);
int					ft_atoi(const char *str);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memalloc(size_t size);
void				*ft_memccpy(void *s1, const void *s2, int c, size_t n);
void				*ft_memcpy(void *s1, const void *s2, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				ft_memdel(void **ap);
void				*ft_memmove(void *s1, const void *s2, size_t n);
char				*ft_strdup(const char *s);
size_t				ft_strlen(const char *str);
char				*ft_strncpy(char *dest, char *src, size_t n);
char				*ft_strcpy(char *s1, const char *s2);
char				*ft_strcat(char *dest, const char *src);
void				ft_strdel(char **as);
char				*ft_strncat(char *dest, const char *src, size_t n);
char				*ft_strnew(size_t size);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *s1, const char *s2);
char				*ft_strnstr(const char *s1, const char *s2, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_atoi(const char *str);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_dtoa(double n);
void				ft_putchar(char c);
void				ft_putstr(const char *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putunbr(unsigned int n);
int					ft_putdbl(double nb, int precision, char *flags);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
void				*ft_realloc(void *mem, size_t new_size);
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void				ft_putstr_color(char *color, char *str, int fd);
int					ft_get_next_line(int fd, char **line);
float				ft_pow(float nbr, int pow);
float				ft_arccos(float nbr);
float				ft_cos(float x);
float				ft_sin(float x);
float				ft_arcsin(float x);
float				ft_arctan(float x);
float				ft_sqrt(float nbr);
float				ft_atof(char *str);
void				ft_putnbr_long(unsigned long long n);
void				ft_puthex(unsigned long val);
char				*ft_ftostr(double nb, int precision);
int					ft_abs(int nb);
void				ft_freearr(char **array);
int					tryint(int err, int res, char *error);
void				*tryptr(void *err, void *res, char *error);
void				putaddr(unsigned long int ptr);
void				ft_putnbr_recursive(int32_t nb, int mult);
int					get_mult(int32_t nb);
void				ft_putchar_hex(unsigned char *c);
void				ft_putint_hex(unsigned int *c);

#endif
