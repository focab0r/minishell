/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igsanche <igsanche@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 12:39:58 by igsanche          #+#    #+#             */
/*   Updated: 2024/01/13 13:11:07 by igsanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		len;

	len = ft_strlen(str);
	if ((char)c == 0)
	{
		return ((char *)(str + len));
	}
	while (len >= 0)
	{
		if (str[len] == (char)c)
		{
			return ((char *)(str + len));
		}
		len--;
	}
	return (NULL);
}

/*
int main(void)
{
	char str[] = "bonjour";
	printf("%s", ft_strrchr(str, 'b'));
}
*/