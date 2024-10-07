/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igsanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:56:32 by igsanche          #+#    #+#             */
/*   Updated: 2024/01/13 14:59:42 by igsanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	if ((str1 == NULL && str2 == NULL) || n == 0)
	{
		return (0);
	}
	while (str1[i] != '\0' && str2[i] != '\0' && i < n)
	{
		if (str1[i] - str2[i] != 0)
		{
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		}
		i++;
	}
	if ((str1[i] == '\0' || str2[i] == '\0') && i < n)
	{
		return ((unsigned char)str1[i] - (unsigned char)str2[i]);
	}
	return ((unsigned char)str1[i - 1] - (unsigned char)str2[i - 1]);
}

/*
int main()
{
    char *str1 = "abcd";
    char *str2 = "abcd";
    printf("%d\n", ft_strncmp("1234", "1235", -1));
}
*/