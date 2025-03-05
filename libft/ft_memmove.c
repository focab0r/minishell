/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igsanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:56:32 by igsanche          #+#    #+#             */
/*   Updated: 2024/01/13 14:59:42 by igsanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	char			*dest2;
	const char		*src2;

	dest2 = dest;
	src2 = src;
	if (src2 == NULL && dest2 == NULL)
		return (NULL);
	if (src2 < dest2 && n != 0)
	{
		while (n != 0)
		{
			dest2[n - 1] = src2[n - 1];
			n--;
		}
		dest2[0] = src2[0];
		return (dest);
	}
	i = 0;
	while (i < n)
	{
		dest2[i] = src2[i];
		i++;
	}
	return (dest);
}

/*
int main(void)
{
	char j[] = "hola buenas";
	char a[] = "jajsjio";
	ft_memmove(j, a, 5);
	printf("%s", j);
	return (0);
}
*/