/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igsanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:56:32 by igsanche          #+#    #+#             */
/*   Updated: 2024/01/25 18:09:48 by igsanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	int		i;
	char	*str11;
	char	*str22;

	str11 = (char *) str1;
	str22 = (char *) str2;
	i = 0;
	if ((str1 == NULL && str2 == NULL) || n == 0)
	{
		return (0);
	}
	while (i < (int)n)
	{
		if (str11[i] - str22[i] != 0)
		{
			return ((unsigned char)str11[i] - (unsigned char)str22[i]);
		}
		i++;
	}
	return ((unsigned char)str11[i - 1] - (unsigned char)str22[i - 1]);
}
/*
int main()
{
	char *str1 = "abcd";
	char *str2 = "abcd";
	printf("%d\n", ft_strncmp("teste", "teste", 7));
}
*/
