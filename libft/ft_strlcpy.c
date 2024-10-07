/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igsanche <igsanche@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:25:31 by igsanche          #+#    #+#             */
/*   Updated: 2024/01/13 09:06:24 by igsanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	unsigned int	i;

	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		if (dest[i] == '\0')
		{
			return (ft_strlen(src));
		}
		i++;
	}
	if (n != 0)
	{
		dest[i - 1] = '\0';
	}
	return (ft_strlen(src));
}
/*
int main()
{
	//char src[10] = "lorem ipsum";
	char dst[5];
	ft_strlcpy(dst, "lorem ipsum", 3);
	printf("%s", dst);

}
*/