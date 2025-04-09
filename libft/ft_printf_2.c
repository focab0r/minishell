/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssousmat <ssousmat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:56:06 by ssousmat          #+#    #+#             */
/*   Updated: 2025/04/09 17:11:49 by ssousmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_dist_n_2(int n, char format)
{
	if (format == 'd' || format == 'i')
	{
		if (n == -2147483648)
			return (write(2, "-2147483648", 11));
		else if (n < 0)
			return (ft_putchar_2('-') + ft_base_2(n * -1, "0123456789"));
		else
			return (ft_base_2(n, "0123456789"));
	}
	else if (format == 'u')
		return (ft_base_2((unsigned int)n, "0123456789"));
	else if (format == 'x')
		return (ft_base_2((unsigned int)n, "0123456789abcdef"));
	else if (format == 'X')
		return (ft_base_2((unsigned int)n, "0123456789ABCDEF"));
	else
		return (-1);
}

int	ft_main_dist_2(char const format, va_list argv)
{
	if (format == '%')
		return (ft_putchar_2('%'));
	else if (format == 'c')
		return (ft_putchar_2(va_arg(argv, int)));
	else if (format == 's')
		return (ft_putstr_2(va_arg(argv, char const *)));
	else if (format == 'p')
		return (ft_putptr_2(va_arg(argv, void *)));
	else
		return (ft_dist_n_2(va_arg(argv, int), format));
}

int	ft_printf_2(char const *format, ...)
{
	int		bytes;
	int		aux;
	char	*str;
	va_list	argv;

	bytes = 0;
	str = (char *)format;
	va_start(argv, format);
	while (*str && bytes >= 0)
	{
		if (*str == '%')
		{
			str++;
			aux = ft_main_dist_2(*str, argv);
			if (aux >= 0)
				bytes += aux;
			else
				bytes = aux;
		}
		else
			bytes += ft_putchar_2(*str);
		if (*str != '\0')
			str++;
	}
	return (va_end(argv), bytes);
}
