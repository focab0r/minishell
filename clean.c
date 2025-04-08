/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssousmat <ssousmat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:56:32 by igsanche          #+#    #+#             */
/*   Updated: 2025/04/08 17:43:29 by ssousmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_line(t_line *line)
{
	int	i;

	i = 0;
	if (line)
	{
		if (line->commands)
		{
			while (i < line->ncommands)
			{
				clean_command(line->commands[i]);
				i++;
			}
			free(line->commands);
		}
		free(line);
	}
}

void	clean_command(t_command command)
{
	int	i;

	i = 0;
	if (command.filename)
		free(command.filename);
	if (command.redirect_input)
		free(command.redirect_input);
	if (command.redirect_output)
		free(command.redirect_output);
	if (command.append_input)
		free(command.append_input);
	if (command.append_output)
		free(command.append_output);
	if (command.argv)
	{
		while (i <= command.argc && command.argc)
		{
			if (command.argv[i])
				free(command.argv[i]);
			i++;
		}
		free(command.argv);
	}
}

void	clean_env(char **env)
{
	int	i;

	i = 0;
	if (env)
	{
		while (env[i])
		{
			if (env[i])
				free(env[i]);
			i++;
		}
		free(env);
	}
}

void	clean_all(t_minishell *minishell)
{
	clean_line(minishell->line);
	clean_env(minishell->env);
}
