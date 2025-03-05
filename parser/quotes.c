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

#include "../minishell.h"

int	calc_quotes_len(char *str)
{
	int		i;
	char	quote;
	int		len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			quote = str[i];
			i++;
			while (str[i] != quote)
			{
				len++;
				i++;
			}
		}
		else
			len++;
		i++;
	}
	return (len);
}

char	*escape_quotes(char *str)
{
	int		len;
	char	*new_str;
	int		i;
	char	quote;

	len = calc_quotes_len(str);
	new_str = (char *) malloc ((len + 1) * sizeof(char));
	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			quote = str[i];
			i++;
			while (str[i] != quote)
				new_str[len++] = str[i++];
		}
		else
			new_str[len++] = str[i];
		i++;
	}
	new_str[len] = '\0';
	free(str);
	return (new_str);
}
