/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igsanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:56:32 by igsanche          #+#    #+#             */
/*   Updated: 2024/01/13 14:59:42 by igsanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	init_var(int *e, int *len, char const *s1, char const *s2)
{
	*e = 0;
	*len = ft_strlen(s1);
	*len += ft_strlen(s2);
	(*len)++;
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	int		i;
	int		e;
	char	*str;

	init_var(&e, &len, s1, s2);
	str = (char *) malloc (len * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[e] != '\0')
	{
		str[i] = s2[e];
		i++;
		e++;
	}
	str[i] = '\0';
	return (str);
}

/*
int main()
{
	char *str1 = "";
	char *str2 = "";
	printf("%s", ft_strjoin(str1, str2));
}
*/