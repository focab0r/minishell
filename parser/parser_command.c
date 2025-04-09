/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssousmat <ssousmat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:56:32 by igsanche          #+#    #+#             */
/*   Updated: 2025/04/09 12:26:36 by ssousmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pc_redirect_double(t_minishell *m, t_command *c, char *pw, char *word)
{
	if (ft_strncmp(pw, ">>", 3) == 0)
	{
		create_file_on_append(word);
		if (c->append_output)
			free(c->append_output);
		c->append_output = word;
	}
	else if (ft_strncmp(pw, "<<", 3) == 0)
	{
		if (c->append_input)
			pipex_manage_input_heredoc(c->append_input, m, false);
		if (c->append_input)
			free(c->append_input);
		c->append_input = word;
	}
}

void	pc_redirect_single(t_command *c, char *prev_word, char *word)
{
	if (ft_strncmp(prev_word, ">", 2) == 0)
	{
		create_file_on_redirect(word);
		if (c->redirect_output)
			free(c->redirect_output);
		c->redirect_output = word;
	}
	else if (ft_strncmp(prev_word, "<", 2) == 0)
	{
		if (c->redirect_input)
			free(c->redirect_input);
		c->redirect_input = word;
	}
}

int	pc_redirects(char *word, t_command *c, t_minishell *mini, char *prev_word)
{
	if (word == NULL || word[0] == '>' || word[0] == '<')
		return (free(prev_word), free(word), 1);
	pc_redirect_double(mini, c, prev_word, word);
	pc_redirect_single(c, prev_word, word);
	free(prev_word);
	return (0);
}

int	pc_argv(t_minishell *minishell, int ifn, t_command *command, char *word)
{
	char		*str;

	if (ifn)
	{
		ifn = 0;
		str = expand_alias(word, minishell);
		if (str)
		{
			command->filename = ft_strdup(str);
			add_argument_at_end(command, str);
		}
		else
		{
			command->filename = ft_strdup(word);
			add_argument_at_end(command, ft_strdup(word));
		}
		free(word);
	}
	else
		add_argument_at_end(command, word);
	return (ifn);
}

t_command	*parse_command(char *input, int *i, t_minishell *minishell)
{
	t_command	*command;
	char		*word;
	char		*word2;
	int			is_filename;

	command = (t_command *) malloc (sizeof(t_command));
	init_command(command);
	is_filename = 1;
	while (input[*i] && input[*i] != '|')
	{
		word = parse_word(input, i, minishell);
		if (word == NULL)
			return (clean_command(*command), free(command), NULL);
		if (word[0] == '<' || word[0] == '>')
		{
			word2 = parse_word(input, i, minishell);
			if (pc_redirects(word2, command, minishell, word) == 1)
				return (clean_command(*command), free(command), NULL);
		}
		else
			is_filename = pc_argv(minishell, is_filename, command, word);
	}
	return (command);
}
