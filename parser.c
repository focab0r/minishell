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

char *parse_word(char *input, int *i)
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

c_list parse_command(char *input, int *i)
{
	c_list	list;
	char	*word;

	list = (t_command *) malloc (sizeof(t_command));
	init_command(&list);
	word = parse_word(input, i);
	list->filename = word;
	while (input[*i] && !is_special_char(input[*i]))
	{
		word = parse_word(input, i);
		add_argument_at_end(&list, word);
	}
	return list;
}

void save_commands(t_line *line, char *input)
{
    int 	i;
	c_list	list;

    i = 0;
	while(input[i])
	{
		list = parse_command(input, &i);
		add_command_at_end(line, list);
		if (is_special_char(input[i]))
		{
			if (input[i] == '<')
			{
				i++;
				line->redirect_input = parse_word(input, &i);
			}
			else if (input[i] == '>')
			{
				i++;
				line->redirect_output = parse_word(input, &i);
			}
			if (input[i] == '|')
				i++;
		}
	}
}

void print_line(t_line *line)
{
	ft_printf("--------------------------------\n");
	ft_printf("Nº commands: %d\n", line->ncommands);
	int i = 0;
	int e;
	while (i < line->ncommands)
	{
		t_command c = (line->commands)[i];
		ft_printf("<<<<< %d >>>>>\n", i);
		ft_printf("--> Command name: %s\n", c.filename);
		ft_printf("--> Nº Argc: %d\n", c.argc);
		e = 0;
		while (e < c.argc)
		{
			ft_printf("----> Arg: %s\n", (c.argv)[e]);
			e++;
		}
		i++;
	}
	if (line->redirect_input != NULL)
		ft_printf("Input redirected to: %s\n", line->redirect_input);
	if (line->redirect_output != NULL)
		ft_printf("Output redirected to: %s\n", line->redirect_output);
	ft_printf("--------------------------------\n");
}

void parse_input(t_line *line, char *input)
{
    line->background = 0;
    line->redirect_input = NULL;
    line->redirect_output = NULL;
    line->redirect_error = NULL;
    line->commands = NULL;
	line->ncommands = 0;
    save_commands(line, input);
	print_line(line);
}