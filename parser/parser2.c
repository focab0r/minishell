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

// void print_line(t_line *line)
// {
// 	ft_printf("--------------------------------\n");
// 	ft_printf("Nº commands: %d\n", line->ncommands);
// 	int i = 0;
// 	int e;
// 	while (i < line->ncommands)
// 	{
// 		t_command c = (line->commands)[i];
// 		ft_printf("<<<<< %d >>>>>\n", i);
// 		ft_printf("--> Command name: %s\n", c.filename);
// 		ft_printf("--> Nº Argc: %d\n", c.argc);
// 		e = 0;
// 		while (e < c.argc)
// 		{
// 			ft_printf("----> Arg: %s\n", (c.argv)[e]);
// 			e++;
// 		}
// 		if (c.redirect_output != NULL)
// 			ft_printf("--> Output redirected to: %s\n", c.redirect_output);
// 		if (c.redirect_input != NULL)
// 			ft_printf("--> Input redirected to: %s\n", c.redirect_input);
// 		if (c.append_output != NULL)
// 			ft_printf("--> Output appended to: %s\n", c.append_output);
// 		if (c.append_input != NULL)
// 			ft_printf("--> Input appended to: %s\n", c.append_input);
// 		i++;
// 	}
// 	ft_printf("--------------------------------\n");
// }