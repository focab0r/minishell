/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_m.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssousmat <ssousmat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 19:19:49 by ssousmat          #+#    #+#             */
/*   Updated: 2025/02/05 19:22:00 by ssousmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_m(char **m)
{
	size_t	i;

	i = 0;
	if (m)
	{
		while (m[i])
			free(m[i++]);
		free(m);
	}
}
