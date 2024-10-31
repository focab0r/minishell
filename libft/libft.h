/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igsanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:56:32 by igsanche          #+#    #+#             */
/*   Updated: 2024/01/13 14:59:42 by igsanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>

typedef struct s_data
{
        int             is_path;
        char    **path;
        int             is_infile;
        int             rd_infile;
        int             is_outfile;
        int             wr_outfile;
        int             **pipes;
        int             prev;
}       t_data;
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

int		ft_isalpha(int n);
int		ft_isdigit(int n);
int		ft_isalnum(int n);
int		ft_isascii(int n);
int		ft_isprint(int n);
size_t	ft_strlen(const char *str);
void	*ft_memset(void *str, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
int		ft_memcmp(const void *str1, const void *str2, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t n);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
int		ft_toupper(int ch);
int		ft_tolower(int ch);
char	*ft_strchr(const char *str, int c);
char	*ft_strrchr(const char *str, int c);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
void	*ft_memchr(const void *str, int c, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
long	ft_atoi(const char *str);
void	*ft_calloc(size_t nitems, size_t size);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *string);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_putnbr_base(unsigned long nbr, char *base);
int		ft_printf(char const *line, ...);
int		ft_symbol_decide(char letter, va_list args);
int		puxx(char letter, va_list args);
int		ft_putnbr_fd_counter(int n);
char	*get_next_line(int fd);
char	*prepare_str(int fd, char **str_saved, int *error, int op);
char	*read_while(int *cr_f, int *error, char **str, char **str_saved);
char	*str_saved_contains_n(char **str, int *i, char **str_saved);
char	*return_str(int error, char **str2, char **str, char **str_saved);
char	*ft_realloc(char *str, int amount);
size_t	strlcpy_and_strlen(char *dest, const char *src, size_t n, int op);
char	*clean(char **str, int *error, int malloc_value, int op);
char	*read_founded(int *error, char **str, char **str_saved, int i_offset);
char	*read_continue(int *cr_f, int *offset, char **str, int *error);
int     ft_pipe(int argc, char **argv, char **env);
#endif