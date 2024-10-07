/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igsanche <igsanche@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 11:19:32 by igsanche          #+#    #+#             */
/*   Updated: 2023/07/20 15:00:52 by igsanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	get_length(char *base)
{
	int	i;

	i = 0;
	while (base[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	print_final(char *base, int *final)
{
	char	a;
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (final[i] != -1)
	{
		i++;
	}
	i--;
	while (i != -1)
	{
		a = base[final[i]];
		write(1, &a, 1);
		count++;
		i--;
	}
	return (count);
}

int	check_characters(char *base)
{
	int	ascii[130];
	int	i;
	int	ch;

	i = 0;
	while (i < 129)
	{
		ascii[i] = 0;
		i++;
	}
	i = 0;
	while (base[i] != '\0')
	{
		ch = base[i];
		ascii[ch]++;
		if (base[i] == '+' || base[i] == '-')
			return (0);
		if (ascii[ch] > 1)
			return (0);
		i++;
	}
	return (1);
}

int	pass_checks(char *base)
{
	if (base[0] == '\0')
		return (0);
	else if (base[1] == '\0' )
		return (0);
	else if (check_characters(base))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

int	ft_putnbr_base(unsigned long nbr, char *base)
{
	int				i;
	unsigned long	div;
	unsigned long	rest;
	int				base_size;
	int				final[200];

	if (pass_checks(base))
	{
		i = 0;
		base_size = get_length(base);
		while (nbr > 0)
		{
			div = nbr / base_size;
			rest = nbr % base_size;
			final[i] = rest;
			nbr = div;
			i++;
		}
		final[i] = -1;
		return (print_final(base, final));
	}
	return (0);
}
