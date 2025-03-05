/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igsanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:56:32 by igsanche          #+#    #+#             */
/*   Updated: 2024/01/13 14:59:42 by igsanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t		i;
	char		*str2;

	i = 0;
	str2 = str;
	while (i < n)
	{
		str2[i] = c;
		i++;
	}
	return (str);
}

/*
int main(void)
{
	char j[] = "hola buenas";
	ft_memset(j, 'a', -2);
	//memset(j, 'a', -2);
	printf("%s", j);
	return (0);
}
*/