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

int	parse_command_redirect(char *input, int *i, t_command *command, char **env)
{
	char	*word;

	if (input[*i] == '>' && input[(*i) + 1] == '>')
	{
		(*i) = (*i) + 2;
		word = parse_word(input, i, env);
		if (word == NULL)
			return (clean_command(*command), free(command), 1);
		command->append_output = word;
	}
	if (input[*i] == '<' && input[(*i) + 1] == '<')
	{
		(*i) = (*i) + 2;
		word = parse_word(input, i, env);
		if (word == NULL)
			return (clean_command(*command), free(command), 1);
		command->append_input = word;
	}
	return (0);
}

int	parse_command_append(char *input, int *i, t_command *command, char **env)
{
	char	*word;

	if (input[*i] == '>')
	{
		(*i) = (*i) + 1;
		word = parse_word(input, i, env);
		if (word == NULL)
			return (clean_command(*command), free(command), 1);
		command->redirect_output = word;
	}
	if (input[*i] == '<')
	{
		(*i) = (*i) + 1;
		word = parse_word(input, i, env);
		if (word == NULL)
			return (clean_command(*command), free(command), 1);
		command->redirect_input = word;
	}
	return (0);
}

t_command	*parse_command_aux(char *input, int *i, t_command *c, char **env)
{
	while (input[*i] && input[*i] != '|' && is_special_char(input[*i]))
	{
		if (parse_command_redirect(input, i, c, env))
			return (NULL);
		if (parse_command_append(input, i, c, env))
			return (NULL);
	}
	return (c);
}

t_command	*parse_command(char *input, int *i, char **env)
{
	t_command	*command;
	char		*word;

	command = (t_command *) malloc (sizeof(t_command));
	init_command(command);
	word = parse_word(input, i, env);
	if (word == NULL)
		return (free(command), NULL);
	command->filename = expand_alias(word, env);
	if (command->filename != NULL)
	{
		add_argument_at_end(command, expand_alias(word, env));
		free(word);
	}
	else
		add_argument_at_end(command, word);
	while (input[*i] && !is_special_char(input[*i]))
	{
		word = parse_word(input, i, env);
		if (word == NULL)
			return (clean_command(*command), free(command), NULL);
		add_argument_at_end(command, word);
	}
	return (parse_command_aux(input, i, command, env));
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
int	parse_input(t_line **line, char *input, char **env)
{
	int			i;
	t_command	*command;

	*line = (t_line *) malloc (sizeof(t_line));
	(*line)->commands = NULL;
	(*line)->ncommands = 0;
	i = 0;
	while (input[i])
	{
		scape_spaces(input, &i);
		if (input[i])
		{
			command = parse_command(input, &i, env);
			if (command != NULL)
				add_command_at_end(*line, command);
			else
				return (1);
			if (input[i] == '|')
				i++;
		}
	}
	return (0);
}
