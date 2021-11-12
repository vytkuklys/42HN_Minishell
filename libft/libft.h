/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuklys <vkuklys@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 12:29:47 by vkuklys           #+#    #+#             */
/*   Updated: 2021/10/28 19:01:41 by vkuklys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_node
{
	int				num;
	int				sorted;
	struct s_node	*next;
}	t_node;

typedef struct s_data
{
	char			*rotate;
	char			*reverse;
	int				rotate_nr;
	int				reverse_nr;
	int				size;
	int				merge_size;
	int				breakpoint;
}	t_data;

long long		ft_atoi(const char *str);
void			ft_bzero( void *dst, unsigned int n );
void			*ft_calloc( unsigned int num, unsigned int size );
int				ft_isalnum(int arg);
int				ft_isalpha(int arg);
int				ft_isascii(int arg);
int				ft_isdigit(int arg);
int				ft_isprint(int arg);
char			*ft_itoa(int n);
void			*ft_memchr(const void *str, int c, size_t n);
int				ft_memcmp(const void *str1, const void *str2, unsigned int n);
void			*ft_memcpy(void *dest, const void *src, unsigned int n);
void			*ft_memmove(void *dst, const void *src, unsigned int length);
void			*ft_memset(void *str, int c, unsigned int n);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
int				ft_putstr_fd(char *s, int fd);
char			**ft_split(char const *s, char c);
char			*ft_strchr(const char *str, int c);
char			*ft_strdup(const char *str1);
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
char			*ft_strjoin(char **s1, const char *s2);
unsigned int	ft_strlcat(char *dst, const char *src, unsigned int size);
unsigned int	ft_strlcpy(char *dst, const char *src, unsigned int size);
int				ft_strlen(const char *str);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strncmp(const char *str1, const char *str2, size_t n);
char			*ft_strnstr(const char	*big, const char *lil, size_t l);
char			*ft_strrchr(const char *str, int c);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_substr(char const *s, size_t start, size_t len);
int				ft_tolower(int arg);
int				ft_toupper(int arg);
void			ft_lstadd_back(t_node **lst, t_node *new);
void			ft_lstadd_front(t_node **lst, t_node *new);
t_node			*ft_lstclear(t_node **lst);
void			ft_lstdelone(t_node *lst);
void			ft_lstiter(t_node *lst, int (*f)(int));
void			ft_lstprint(t_node *head);
t_node			*ft_lstlast(t_node *lst);
t_node			*ft_lstmap(t_node *lst, int (*f)(int), int (*dl)(t_node *));
t_node			*ft_lstnew(int content);
int				ft_lstsize(t_node *lst);
int				ft_get_digit_count(long long n);
long			ft_pow(int base, int exponent);
int				ft_put_unsigned_int_fd(unsigned int n, int fd);
int				ft_puthexa_fd(unsigned long n, int fd, int upper);
int				get_min(int a, int b);
char			*ft_free_2d_array(char ***arr, unsigned int allocated);
int				ft_strlen_2d(char **s);
int				ft_strrstr(const char *big, const char *lil);
char			*ft_triple_strjoin(char **s1, char const *s2, char const *s3,
					int len_s1);
int				ft_strcmp(char *s1, char *s2);
int				check_builtin_command(char *cmd);
char			**get_path(char *envp[]);
char			*ft_strjoin2(char **s1, const char *s2);
char			*ft_strjoin_status(char *s1, char *s2);
char			*ft_strtrim_free(char const *s1, char const *set);
char			*ft_substr_free(char const *s, size_t start, size_t len);
char			*get_next_line(int fd);
int				get_int_sum(int *arr, int size);

#endif
