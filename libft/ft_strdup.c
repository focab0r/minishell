/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igsanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:56:32 by igsanche          #+#    #+#             */
/*   Updated: 2024/01/13 14:59:42 by igsanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *string)
{
	int		len;
	char	*str2;
	int		i;

	i = 0;
	len = ft_strlen(string);
	str2 = (char *) malloc ((len + 1) * sizeof(char));
	if (str2 == NULL)
	{
		return (NULL);
	}
	while (string[i] != '\0')
	{
		str2[i] = string[i];
		i++;
	}
	str2[i] = '\0';
	return (str2);
}

/*
int main()
{
	char *str2 = "";
	printf ("%s", ft_strdup(str2));
}
*/