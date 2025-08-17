/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtome-ve <gtome-ve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 15:39:02 by gtome-ve          #+#    #+#             */
/*   Updated: 2024/12/08 17:58:41 by gtome-ve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <ctype.h>
# include <string.h>
# include <unistd.h>
# include <stdint.h>
# include <stdlib.h>
# include <ctype.h>

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

# define INT_BASE "0123456789"
# define HEX_UPP_BASE "0123456789ABCDEF"
# define HEX_LOW_BASE "0123456789abcdef"

int		ft_isalpha(int c);
int		ft_isdigit(int value);
int		ft_isalnum(int value);
int		ft_isascii(int value);
int		ft_isprint(int value);
size_t	ft_strlen(const char *str);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char 	*ft_strncpy(char *dst, const char *src, size_t len);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
size_t	ft_strlen_pf(char *str);
void	ft_putchar_pf(char c, int *count);
void	ft_putnbr_pf(long long nbr, char *base, int *count);
void	ft_putstr_pf(char *str, int *count);
void	ft_putptr_pf(unsigned long long nbr, int *count);
int		ft_fillformat_pf(va_list lst, char c, int *count);
int		ft_printf(char const *str, ...);
void	ft_putstr_or_ptr_pf(char *str, int *count, int is_ptr);
void	ft_putdata_pf(long long nbr, char *base, int *count, int is_signed);
char *ft_strstr(const char *haystack, const char *needle);
char *ft_strncpy(char *dst, const char *src, size_t len);

#endif
