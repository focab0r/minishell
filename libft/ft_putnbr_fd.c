/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igsanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:56:32 by igsanche          #+#    #+#             */
/*   Updated: 2024/01/13 14:59:42 by igsanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	putnbr_get_less_zero(int n)
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

void	putnbr_operate(int *zero, int *n, int *i, int fd)
{
	int		m;
	char	c;

	while (*zero >= 1)
	{
		if (*n >= 0)
			c = (*n / *zero) + 48;
		else
			c = -(*n / *zero) + 48;
		write(fd, &c, 1);
		m = *n % *zero;
		*n = m;
		*zero = *zero / 10;
		(*i)++;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	int		a;
	int		zero;
	int		i;
	char	c;

	a = n;
	if (n >= 0)
		a = -n;
	zero = putnbr_get_less_zero(a);
	i = 0;
	if (n < 0)
	{
		c = '-';
		write(fd, &c, 1);
		i = 1;
	}
	putnbr_operate(&zero, &n, &i, fd);
}
