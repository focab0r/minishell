/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igsanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:56:32 by igsanche          #+#    #+#             */
/*   Updated: 2024/01/13 14:59:42 by igsanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(char const *line, ...)
{
	va_list	args;
	int		i;
	int		count;

	va_start(args, line);
	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '%')
		{
			count += ft_symbol_decide(line[i + 1], args);
			i++;
		}
		else
		{
			write(1, &(line[i]), 1);
			count++;
		}
		if (line[i] != '\0')
			i++;
	}
	va_end(args);
	return (count);
}
