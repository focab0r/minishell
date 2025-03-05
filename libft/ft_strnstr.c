/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igsanche <igsanche@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 12:39:58 by igsanche          #+#    #+#             */
/*   Updated: 2024/01/13 13:11:07 by igsanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	init_var_func2(int *i, int *e, int *j)
{
	*j = 0;
	*i = 0;
	*e = 0;
}

void	summarize(int *i, int *e, int *j, size_t *len)
{
	(*j)++;
	*e = 0;
	*i = *j;
	(*len)--;
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		i;
	int		e;
	int		j;
	size_t	len2;

	init_var_func2(&i, &e, &j);
	len2 = len;
	if (*needle == 0)
		return ((char *) haystack);
	while (haystack[j] != '\0' && len > 0)
	{
		while (haystack[i] == needle[e] && haystack[i] != '\0'
			&& needle[e] != '\0' && len2 > 0)
		{
			len2--;
			i++;
			e++;
		}
		if (needle[e] == '\0')
			return ((char *)haystack + i - e);
		summarize(&i, &e, &j, &len);
		len2 = len;
	}
	return (NULL);
}

/*
int main(void)
{
	char str[] = "aaxx";
	printf("%s", ft_strnstr(str, "ax", -1));
}
*/