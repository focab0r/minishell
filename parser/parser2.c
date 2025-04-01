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

void	pass_till_comma(char *input, int *i)
{
	char	elem;

	elem = input[*i];
	(*i)++;
	while (input[*i] && input[*i] != elem)
	{
		(*i)++;
	}
	if (input[*i] == '\0')
		*i = -1;
}

int	is_special_char(char c)
{
	if (c == ' ' || c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

void	scape_spaces(char *input, int *i)
{
	while (input[*i] == ' ')
		(*i)++;
}

char	*parse_word(char *input, int *i, char **env)
{
	char	*start;
	char	*result;
	int		len;

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
	if (input[*i] == '<' || input[*i] == '>')
		*i = *i+1;
	if (input[*i] == '<' || input[*i] == '>')
		*i = *i+1;
	if (&(input[*i]) == start)
		return (NULL);
	len = &(input[*i]) - start;
	result = (char *) malloc ((len + 1) * sizeof(char));
	ft_strlcpy(result, start, len + 1);
	scape_spaces(input, i);
	result = replace_vars(result, env);
	result = escape_quotes(result);
	return (result);
}
