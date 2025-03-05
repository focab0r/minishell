/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igsanche <igsanche@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 12:39:58 by igsanche          #+#    #+#             */
/*   Updated: 2024/01/25 18:27:03 by igsanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_to_num(char a)
{
	return (a - 48);
}

int	ft_strlen_till_char(const char *str)
{
	int	i;

	i = 0;
	while (ft_isdigit(str[i]))
	{
		i++;
	}
	return (i);
}

int	is_especial_char(char c)
{
	if (c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == '\f' || c == ' ')
	{
		return (1);
	}
	return (0);
}

void	get_i(const char *str, int *i, int *neg)
{
	while (is_especial_char(str[*i]))
	{
		(*i)++;
	}
	if (str[*i] == '-' || str[*i] == '+')
	{
		*neg = *i;
		(*i)++;
	}
	while (str[*i] == 48)
	{
		(*i)++;
	}
}

long	ft_atoi(const char *str)
{
	int		i;
	int		len;
	long	zero;
	long	fnum;
	int		neg;

	fnum = 0;
	i = 0;
	len = 0;
	zero = 1;
	neg = 0;
	get_i(str, &i, &neg);
	len = ft_strlen_till_char(&(str[i]));
	while (len-- > 1)
		zero = zero * 10;
	while (ft_isdigit(str[i]))
	{
		fnum = fnum + (ft_to_num(str[i]) * zero);
		zero = zero / 10;
		i++;
	}
	if (str[neg] == '-')
		return (fnum * -1);
	return (fnum);
}
/*
int	main(void)
{
	int num = ft_atoi("+0000000000000000123");
	printf("%d\n", num);
}
*/
