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

void	add_argument_at_end(t_command *command, char *word)
{
	int		i;
	char	**aux;

	if (command->argc == 0)
	{
		command->argv = (char **) malloc (2 * sizeof(char *));
		command->argv[0] = word;
		command->argv[1] = NULL;
		command->argc = 1;
		return ;
	}
	aux = (char **) malloc ((command->argc + 2) * sizeof(char *));
	i = 0;
	while (i < command->argc)
	{
		aux[i] = (command->argv)[i];
		i++;
	}
	aux[i] = word;
	aux[i + 1] = NULL;
	free(command->argv);
	command->argv = aux;
	command->argc++;
}

void	init_command(t_command *l)
{
	l->argv = NULL;
	l->argc = 0;
	l->filename = NULL;
	l->redirect_input = NULL;
	l->redirect_output = NULL;
	l->append_input = NULL;
	l->append_output = NULL;
}

void	add_command_at_end(t_line *line, t_command *command)
{
	int			i;
	t_command	*aux;

	if (line->ncommands == 0)
	{
		line->commands = command;
		line->ncommands = 1;
		return ;
	}
	aux = (t_command *) malloc ((line->ncommands + 1) * sizeof(t_command));
	i = 0;
	while (i < line->ncommands)
	{
		aux[i] = line->commands[i];
		i++;
	}
	aux[i] = *command;
	free(command);
	free(line->commands);
	line->commands = aux;
	line->ncommands++;
}
