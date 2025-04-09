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

char	*save_word(char *input, int *i, char *start)
{
	int		len;
	char	*result;

	if (input[*i] == '<' || input[*i] == '>')
		*i = *i + 1;
	if (input[*i] == '<' || input[*i] == '>')
		*i = *i + 1;
	if (&(input[*i]) == start)
		return (NULL);
	len = &(input[*i]) - start;
	result = (char *) malloc ((len + 1) * sizeof(char));
	ft_strlcpy(result, start, len + 1);
	return (result);
}

char	*parse_word(char *input, int *i, t_minishell *minishell)
{
	char	*start;
	char	*result;

	scape_spaces(input, i);
	start = &(input[*i]);
	while (input[*i] && !is_special_char(input[*i]))
	{
		if (input[*i] == '"' || input[*i] == '\'')
		{
			pass_till_comma(input, i);
			if (*i == -1)
				return (NULL);
		}
		(*i)++;
	}
	result = save_word(input, i, start);
	scape_spaces(input, i);
	result = replace_vars(result, minishell);
	result = escape_quotes(result);
	return (result);
}
