/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssousmat <ssousmat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:56:32 by igsanche          #+#    #+#             */
/*   Updated: 2025/04/09 12:26:36 by ssousmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_file_on_append(char *word)
{
	int	code;

	code = open(word, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (code == -1)
	{
		ft_printf_2("Error: Unable to open %s\n", word);
	}
	else
		close(code);
}

void	create_file_on_redirect(char *word, int control)
{
	int	code;

	if (control)
		code = open(word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		code = open(word, O_WRONLY);
	if (code == -1)
	{
		ft_printf_2("Error: Unable to open %s\n", word);
	}
	else
		close(code);
}

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
