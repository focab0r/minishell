/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igsanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:56:32 by igsanche          #+#    #+#             */
/*   Updated: 2024/01/25 17:44:37 by igsanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t		i;
	char		*str1;

	str1 = (char *) str;
	i = 0;
	if (n == 0)
	{
		return (NULL);
	}
	while (i < n)
	{
		if (str1[i] == (char)c)
		{
			return ((char *)(str + i));
		}
		i++;
	}
	return (NULL);
}
/*
int main(void)
{
	char str[] = {0, 1, 2, 3, 4, 5};
	printf("%s", (char *)ft_memchr(str, 2, 4));
}
*/
