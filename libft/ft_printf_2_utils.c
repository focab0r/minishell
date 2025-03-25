/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_2_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssousmat <ssousmat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 19:03:49 by ssousmat          #+#    #+#             */
/*   Updated: 2025/02/04 19:05:04 by ssousmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar_2(char c)
{
	return (write(2, &c, 1));
}

int	ft_base_2(size_t num, char *base)
{
	size_t	len;

	len = 1;
	if (num >= (size_t)ft_strlen(base))
	{
		len += ft_base_2(num / ft_strlen(base), base);
		ft_putchar_2(base[num % ft_strlen(base)]);
	}
	else
		ft_putchar_2(base[num]);
	return (len);
}

int	ft_putstr_2(char const *str)
{
	if (str)
		return (write(2, str, ft_strlen(str)));
	return (write(2, "(null)", 6));
}

int	ft_putptr_2(void *p)
{
	size_t	n;

	n = (size_t)p;
	write(2, "0x", 2);
	return (ft_base_2(n, "0123456789abcdef") + 2);
}
