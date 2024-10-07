/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_symbol_decide.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igsanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:56:32 by igsanche          #+#    #+#             */
/*   Updated: 2024/01/13 14:59:42 by igsanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_symbol_decide(char letter, va_list args)
{
	char	*str;
	int		val;

	if (letter == 'c')
		return (ft_putchar_fd(va_arg(args, int), 1), 1);
	else if (letter == 's')
	{
		str = va_arg(args, char *);
		if (str == NULL)
			return (write(1, "(null)", 6), 6);
		ft_putstr_fd(str, 1);
		return (ft_strlen(str));
	}
	else if (letter == 'd' || letter == 'i')
	{
		val = va_arg(args, int);
		ft_putnbr_fd(val, 1);
		return (ft_putnbr_fd_counter(val));
	}
	else if (letter == '%')
		return (write(1, "%", 1), 1);
	else if (letter == 'p' || letter == 'u' || letter == 'x' || letter == 'X')
		return (puxx(letter, args));
	return (1);
}

int	puxx(char letter, va_list args)
{
	unsigned long	var;

	if (letter == 'p')
	{
		write(1, "0x", 2);
		var = va_arg(args, unsigned long);
		if (var == 0)
			return (write(1, "0", 1), 3);
		return (ft_putnbr_base(var, "0123456789abcdef") + 2);
	}
	else
	{
		var = va_arg(args, unsigned int);
		if (var == 0)
			return (write(1, "0", 1), 1);
		if (letter == 'u')
			return (ft_putnbr_base(var, "0123456789"));
		else if (letter == 'x')
			return (ft_putnbr_base(var, "0123456789abcdef"));
		else
			return (ft_putnbr_base(var, "0123456789ABCDEF"));
	}
}

int	putnbr_get_less_zero2(int n)
{
	int	i;

	i = -1;
	while (n <= i && i > -1000000000)
	{
		i = i * 10;
	}
	if (n > -10)
	{
		return (1);
	}
	if (i == -1000000000 && n < i)
	{
		return (1000000000);
	}
	return (-i / 10);
}

int	putnbr_operate2(int *zero, int *n)
{
	int		m;
	int		count;

	count = 0;
	while (*zero >= 1)
	{
		count++;
		m = *n % *zero;
		*n = m;
		*zero = *zero / 10;
	}
	return (count);
}

int	ft_putnbr_fd_counter(int n)
{
	int		a;
	int		zero;
	int		count;

	count = 0;
	a = n;
	if (n >= 0)
		a = -n;
	zero = putnbr_get_less_zero2(a);
	if (n < 0)
		count = 1;
	return (putnbr_operate2(&zero, &n) + count);
}
