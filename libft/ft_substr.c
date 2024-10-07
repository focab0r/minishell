/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igsanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:56:32 by igsanche          #+#    #+#             */
/*   Updated: 2024/01/25 17:53:04 by igsanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	size_t	e;
	char	*str;

	if (start > ft_strlen(s))
	{
		str = (char *) malloc (1 * sizeof (char));
		if (str == NULL)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	i = start;
	if (len > ft_strlen(&(s[start])))
		str = (char *) malloc ((ft_strlen(&(s[start])) + 1) * sizeof(char));
	else
		str = (char *) malloc ((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	e = 0;
	while (s[i] != '\0' && e < len)
		str[e++] = s[i++];
	str[e] = '\0';
	return (str);
}

/*
int main()
{
	char *str = "hola buenas que tal";
	printf("%s", ft_substr(str, 6, 10));
}
*/
