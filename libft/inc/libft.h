/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 18:44:21 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/06/08 19:08:38 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include "get_next_line.h"
# define BF_SIZE 8162

typedef long long unsigned int	t_opts;
typedef	struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

double			ft_clamp(double value, double low, double high);
double			ft_max(double value, double low);
char			**tabdup(char **table, char ***new_tab, int addlines);
char			**ft_splitwhitespaces(char const *s);
char			**ft_strsplit(char const *s, char c);
char			**ft_sort_params(char **argv);
char			*ft_strbchr(char *str, char c);
char			*ft_itoa(int n);
char			*ft_strinsert(char *str, char *insertion, size_t location);
char			*ft_strcat(char *restrict s1, const char *restrict s2);
char			*ft_strchr(const char *s, int c);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strdup(const char *s1);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_strncat(char *restrict s1, const char *restrict s2,
		size_t n);
char			*ft_strncpy(char *dst, const char *src, size_t len);
char			*ft_strnew(size_t size);
char			*ft_strnstr(const char *haystack, const char *needle,
		size_t len);
char			*ft_strrchr(const char *s, int c);
char			*ft_strstr(const char *haystack, const char *needle);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strtrim(char const *s);
int				tab_realloc(char ***tab);
int				ft_atoi(const char *str);
int				how_many_lines(const int fd);
int				ft_base_size(long long nb, int base);
int				ft_isalnum(int c);
int				ft_putscap(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
int				ft_lstlen(t_list *lst);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strequ(char const *s1, char const *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
int				ft_tolower(int c);
int				ft_toupper(int c);
int				ft_cat_buffer(char *buffer, char *tocopy, int i);
size_t			ft_strlcat(char *restrict dst, const char *restrict src,
		size_t size);
size_t			ft_strlen(const char *str);
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list			*ft_lstnew(void const *content, size_t content_size);
void			free_tab(char ***tab);
void			*ft_memalloc(size_t size);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memdup(void const *content, size_t content_size);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
void			ft_memdel(void **ap);
void			ft_print_char_tab(char **tab);
void			ft_print_int_tab(int *tab, size_t len);
int				ft_putchar(int c);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl(char const *s);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr(int n);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr(char const *s);
void			ft_putstr_fd(char const *s, int fd);
void			ft_strclr(char *s);
void			ft_strdel(char **as);
void			ft_striter(char *s, void (*f)(char*));
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
void			ft_print_bits(long long unsigned int nbr);
int				ft_sqrt(int nb);
void			ft_tabdel(char ***array);
t_opts			get_options(int argc, char **argv, char *allowed);
int8_t			ft_atol(const char *s, int64_t *result);
int				ft_tablen(char **array);

#endif
