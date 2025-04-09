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

int	iterate_input(t_minishell *minishell, char *input, int *i)
{
	int			pipe;
	t_command	*command;

	pipe = 0;
	command = parse_command(input, i, minishell);
	if (command != NULL)
	{
		if (command->append_input && !command->filename)
			pipex_manage_input_heredoc(command->append_input, minishell, false);
		add_command_at_end(minishell->line, command);
	}
	else
		return (1);
	if (input[*i] == '|')
	{
		(*i)++;
		pipe = 1;
	}
	return (pipe);
}

int	parse_input(char *input, t_minishell *minishell)
{
	int			i;
	int			pipe;

	minishell->line = (t_line *) malloc (sizeof(t_line));
	minishell->line->commands = NULL;
	minishell->line->ncommands = 0;
	i = 0;
	while (input[i])
	{
		pipe = 0;
		scape_spaces(input, &i);
		if (input[i] == '|')
			return (1);
		if (input[i])
			pipe = iterate_input(minishell, input, &i);
		scape_spaces(input, &i);
	}
	if (pipe)
		return (1);
	return (0);
}
