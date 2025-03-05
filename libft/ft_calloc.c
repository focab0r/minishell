/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igsanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:56:32 by igsanche          #+#    #+#             */
/*   Updated: 2024/01/25 17:23:46 by igsanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *) malloc (nitems * size);
	if (str == NULL)
	{
		return (NULL);
	}
	while (i < nitems * size)
	{
		str[i] = '\0';
		i++;
	}
	return (str);
}

/*
int main()
{
	int *str = ft_calloc(5, sizeof(int));
	str[0] = 1;
	printf("%d", str[0]);
}
*/
