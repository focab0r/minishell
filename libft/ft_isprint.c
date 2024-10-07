/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igsanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:56:32 by igsanche          #+#    #+#             */
/*   Updated: 2024/01/13 14:59:42 by igsanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int n)
{
	if (32 <= n && n <= 126)
		return (1);
	return (0);
}

/*
int main(void)
{
	char j = 1;
	for (int i = 0; i < 200; i++)
	{
		printf("Numero %d es %i\n", i, ft_isprint(i));
	}
	return (0);
}
*/