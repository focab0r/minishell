/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssousmat <ssousmat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 20:29:41 by ssousmat          #+#    #+#             */
/*   Updated: 2025/03/25 18:22:22 by ssousmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_isnum(char *str)
{
	size_t	i;
	bool	digit;

	i = 0;
	digit = false;
	if (!str)
		return (false);
	while (str[i] == ' ')
		i++;
	if (ft_issign(str[i]))
		i++;
	while (ft_isdigit(str[i]))
	{
		digit = true;
		i++;
	}
	while (str[i] == ' ')
		i++;
	if (digit && (str[i] == '\0'))
		return (true);
	return (false);
}
