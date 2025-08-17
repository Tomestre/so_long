/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtome-ve <gtome-ve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 20:31:11 by gtome-ve          #+#    #+#             */
/*   Updated: 2025/08/16 18:50:39 by gtome-ve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	handle_char_string(va_list lst, char c, int *count)
{
	if (c == 'c')
		ft_putchar_pf((char)va_arg(lst, int), count);
	else if (c == 's')
		ft_putstr_or_ptr_pf(va_arg(lst, char *), count, 0);
	else if (c == 'p')
		ft_putstr_or_ptr_pf(va_arg(lst, void *), count, 1);
}

static void	handle_numbers(va_list lst, char c, int *count)
{
	if (c == 'd' || c == 'i')
		ft_putdata_pf((long long)va_arg(lst, int), INT_BASE, count, 1);
	else if (c == 'u')
	{
		ft_putdata_pf((unsigned long long)va_arg(lst, unsigned int),
			INT_BASE, count, 0);
	}
	else if (c == 'x')
	{
		ft_putdata_pf((unsigned long long)va_arg(lst, unsigned int),
			HEX_LOW_BASE, count, 0);
	}
	else if (c == 'X')
	{
		ft_putdata_pf((unsigned long long)va_arg(lst, unsigned int),
			HEX_UPP_BASE, count, 0);
	}
}

int	ft_fillformat_pf(va_list lst, char c, int *count)
{
	if (!count)
		return (-1);
	if (c == 'c' || c == 's' || c == 'p')
		handle_char_string(lst, c, count);
	else if (c == 'd' || c == 'i' || c == 'u' || c == 'x' || c == 'X')
		handle_numbers(lst, c, count);
	else if (c == '%')
		ft_putchar_pf('%', count);
	return (0);
}

int	ft_printf(char const *str, ...)
{
	va_list	lst;
	int		count;
	int		i;

	count = 0;
	i = 0;
	if (!str)
		return (-1);
	va_start(lst, str);
	while (str[i] && count != -1)
	{
		if (str[i] != '%')
			ft_putchar_pf(str[i], &count);
		else
		{
			i++;
			ft_fillformat_pf(lst, str[i], &count);
		}
		i++;
	}
	va_end(lst);
	return (count);
}
