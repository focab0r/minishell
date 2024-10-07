/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igsanche <igsanche@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 12:39:58 by igsanche          #+#    #+#             */
/*   Updated: 2024/01/29 12:00:31 by igsanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	init_var_func(unsigned int *i, int *e, int *flag)
{
	*flag = 0;
	*i = 0;
	*e = 0;
}

void	dest_func(char *dest, unsigned int *i, size_t *size, int *flag)
{
	while (dest[*i] != '\0' && *i < (unsigned int) *size)
	{
		dest[*i] = dest[*i];
		(*i)++;
		*flag = 1;
	}
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int	i;
	int				s;
	int				e;
	int				flag;

	init_var_func(&i, &e, &flag);
	s = ft_strlen(dest);
	dest_func(dest, &i, &size, &flag);
	while (src[e] != '\0' && i < size)
	{
		dest[i++] = src[e++];
		flag = 2;
	}
	if (src[e] == '\0' && i < size)
		dest[i] = '\0';
	else if (flag == 2)
	{
		if (i > 0)
			dest[i - 1] = '\0';
	}
	if (flag == 2 || dest[i] == '\0')
		return (s + ft_strlen(src));
	else
		return (size + ft_strlen(src));
}

/*
int main()
{
	char src[15] = "abcd";
	char dest[15] = "pqrstuvwxyz";
	ft_strlcat(dest, src, 2);
	printf("%s", dest);
}
*/
