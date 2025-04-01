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

void	create_file_on_append(char *word)
{
	int code;

	code = open(word, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (code == -1)
	{
		ft_printf_2("Error: Unable to open %s\n", word);
	}
	else
		close(code);
}

void	create_file_on_redirect(char *word)
{
	int code;

	code = open(word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (code == -1)
	{
		ft_printf_2("Error: Unable to open %s\n", word);
	}
	else
		close(code);
}

int	parse_command_redirects(char *input, int *i, t_command *c, char **env, char *prev_word)
{
	char	*word;
	int		code;

	word = parse_word(input, i, env);
	if (word == NULL || word[0] == '>' || word[0] == '<')
		return (free(prev_word), free(word), 1);

	if (ft_strncmp(prev_word, ">>", 3) == 0)
	{
		create_file_on_append(word);
		c->append_output = word;
	}
	else if (ft_strncmp(prev_word, "<<", 3) == 0)
	{
		c->append_input = word;
	}
	else if (ft_strncmp(prev_word, ">", 2) == 0)
	{
		create_file_on_redirect(word);
		c->redirect_output = word;
	}
	else if (ft_strncmp(prev_word, "<", 2) == 0)
	{
		c->redirect_input = word;
	}
	return (0);
}

t_command	*parse_command(char *input, int *i, char **env)
{
	t_command	*command;
	char		*word;
	int			is_filename;

	command = (t_command *) malloc (sizeof(t_command));
	init_command(command);
	is_filename = 1;
	while (input[*i] && input[*i] != '|')
	{
		word = parse_word(input, i, env);
		if (word == NULL)
			return (free(command), NULL);
		if (word[0] == '<' || word[0] == '>')
		{
			if (parse_command_redirects(input, i, command, env, word) == 1)
				return (free(command), NULL);
		}
		else
		{
			if (is_filename)
			{
				is_filename = 0;
				command->filename = expand_alias(word, env);
				if (command->filename != NULL)
				{
					add_argument_at_end(command, expand_alias(word, env));
					free(word);
				}
				else
					add_argument_at_end(command, word);
			}
			else
				add_argument_at_end(command, word);
		}
	}
	return (command);
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
