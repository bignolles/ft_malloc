/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/20 22:33:09 by marene            #+#    #+#             */
/*   Updated: 2016/05/17 14:23:26 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/*
** this header contains all the prototypes required for the creation of libft.a
** libft.a is a very usefull archives which contains re-coded libc functions,
** and a few other memory and char strings manipulation functions.
*/

# include <string.h>
# include <unistd.h>
# include <stdlib.h>

# define MIN_INT		-2147483648
# define BLANK_CHARS	" \n\t\v\r\f"
# define MIN(a,b)		((a < b) ? a : b)
# define MAX(a,b)		((a > b) ? a : b)

typedef struct	s_list
{
	int				index;
	int				select;
	char			*name;
	struct s_list	*next;
}				t_list;

typedef struct	s_dlist
{
	char			*content;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}				t_dlist;

/*
** |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
** |	string manipulation functions	|
** |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
*/

char			*ft_epurstr(char *str);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char c));
char			*ft_strncat(char *s1, const char *s2, size_t len);
char			*ft_strncpy(char *s1, const char *s2, size_t len);
char			*ft_strrchr(const char *s, char c);
char			*ft_strnstr(const char *s1, const char *s2, size_t len);
char			**ft_strsplit(char const *s, char c);
char			**ft_ws_split(char const *s);
char			*ft_strstr(const char *s1, const char *s2);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strcpy(char *s1, const char *s2);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strchr(const char *s1, int n);
char			*ft_strtrim(char const *s1);
char			*ft_strdup(const char *s1);
char			*ft_strnew(size_t len);
void			ft_striteri(char *s1, void (*f)(unsigned int, char*));
void			ft_striter(char *s1, void (*f)(char*));
void			ft_strdel(char **s1);
void			ft_strclr(char *s1);
size_t			ft_strlcat(char *s1, const char *s2, size_t len);
size_t			ft_strlen(const char *s1);
int				ft_strnequ(char const *s1, char const *s2, size_t len);
int				ft_strncmp(const char *s1, const char *s2, size_t len);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strequ(char const *s1, char const *s2);

/*
** |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
** |	memory manipulation fuctions	|
** |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
*/

void			*ft_memccpy(void *p1, const void *p2, int n, size_t len);
void			*ft_memcpy(void *p1, const void *p2, size_t len);
void			*ft_memmove(void *p1, const void *p2, size_t len);
void			*ft_memchr(const void *p1, int n, size_t len);
void			*ft_memset(void *p1, int n, size_t len);
void			ft_bzero(void *p1, size_t len);
void			*ft_memalloc(size_t len);
void			ft_memdel(void **p1);
int				ft_memcmp(const void *p1, const void *p2, size_t len);

/*
** |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
** |		prompting functions			|
** |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
*/

void			ft_putnbr(int n);
void			ft_putchar(char c);
void			ft_putendl_fd(char const *s, int n);
void			ft_putnbr_fd(int n1, int n2);
void			ft_putstr(char const *s);
void			ft_putstr_fd(const char *s1, int n);
void			ft_putchar_fd(char c, int n);
void			ft_putendl(char const *s);

/*
** |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
** |			miscellaneous			|
** |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
*/

int				ft_array_len(char **array);
int				ft_atoi(const char *s1);
char			*ft_itoa(int n);
int				ft_isdigit(int n);
int				ft_isalpha(int n);
int				ft_isascii(int n);
int				ft_isprint(int n);
int				ft_isalnum(int n);
int				ft_isnumber(char *str);
int				ft_iswhite(char c);
int				ft_toupper(int n);
int				ft_tolower(int n);
void			ft_usage(char *exname);
void			putaddr(unsigned long int ptr, int fd);
void			ft_putnbr_recursive(int32_t nb, int mult, int fd);
int				get_mult(int32_t nb);
void			ft_putchar_hex(unsigned char *c);
void			ft_putint_hex(unsigned int *c);
void			ft_putstr_dump(char *str, int len);
int				ft_abs(int nb);

/*
** |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
** |	linked list manipulation functions	|
** |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
*/

t_dlist			*ft_dlist_create(char *s1);
int				ft_dlist_add(t_dlist **root, t_dlist *elem);
t_list			*ft_new_elem(char *s1);
int				ft_list_add(t_list **root, t_list *elem);

#endif
