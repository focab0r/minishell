/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igsanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:56:32 by igsanche          #+#    #+#             */
/*   Updated: 2024/01/13 14:59:42 by igsanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_less_zero(int n)
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

void	operate(int *zero, int *n, int *i, char	*str)
{
	int	m;

	while (*zero >= 1)
	{
		if (*n >= 0)
			str[*i] = (*n / *zero) + 48;
		else
			str[*i] = -(*n / *zero) + 48;
		m = *n % *zero;
		*n = m;
		*zero = *zero / 10;
		(*i)++;
	}
}

int	calc_len(int n, int zero)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		i = 1;
	}
	while (zero >= 1)
	{
		zero = zero / 10;
		i++;
	}
	return (i + 1);
}

char	*ft_itoa(int n)
{
	int		a;
	int		zero;
	char	*str;
	int		i;

	a = n;
	if (n >= 0)
		a = -n;
	zero = get_less_zero(a);
	str = (char *) malloc (calc_len(n, zero) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	if (n < 0)
	{
		str[0] = '-';
		i = 1;
	}
	operate(&zero, &n, &i, str);
	str[i] = '\0';
	return (str);
}

/*
int main()
{
	char *str = ft_itoa(-508298100);
	printf("%s",  str);
}
*/