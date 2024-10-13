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

#include "minishell.h"


void pass_till_comma(char *input, int *i)
{
    char	elem;

	elem = input[*i];
	(*i)++;
	while (input[*i] && input[*i] != elem)
	{
		(*i)++;
	}
	if (!input[*i])
		*i = -1;
}

int	is_special_char(char c)
{
	if (c == ' ' || c == '|' || c == '>' || c == '<')
		return (1);
	return(0);
}

char *parse_word(t_line *line, char *input, int *i)
{
    char	*start;
	char	*result;
	int		len;

	while (input[*i] == ' ')
		(*i)++;
	start = &(input[*i]);
	while (input[*i] && !is_special_char(input[*i]))
	{
		if (input[*i] == '"' || input[*i] == '\'')
		{
			pass_till_comma(input, i);
			if (*i == -1)
				exit(42);
		}
		(*i)++;
	}
	if (&(input[*i]) == start)
		exit(42);
	len = &(input[*i]) - start;
	result = (char *) malloc ((len+1) * sizeof(char));
	ft_strlcpy(result, start, len+1);
	while (input[*i] == ' ')
		(*i)++;
	return (result);
}

void save_commands(t_line *line, char *input)
{
    int 	i;
	int		finished;
	c_list	list;

    i = 0;
	finished = 0;
	while(input[i])
	{
		list = (t_command *) malloc (sizeof(t_command));
		init_command(&list);
		list->filename = parse_word(line, input, &i);
		while (input[i] && !is_special_char(input[i]))
		{
			add_argument_at_end(&list, parse_word(line, input, &i));
		}
		if (is_special_char(input[i]))
		{
			ft_printf("ESPECIAL ARG: %c\n", input[i]);
			i++;
		}
	}
}

void parse_input(char *input)
{
    t_line line;

    line.background = 0;
    line.redirect_input = NULL;
    line.redirect_output = NULL;
    line.redirect_error = NULL;
    line.commands = NULL;
    //line.ncommands = count_commands(input);
    save_commands(&line, input);
}