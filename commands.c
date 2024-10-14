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

void add_argument_at_end(c_list *l, char *word)
{
	int		len;
	int		i;
	char	**new_argv;

	if ((*l)->argc == 0)
	{
		(*l)->argv = (char **) malloc (sizeof(char *));
		((*l)->argv)[0] = word;
		((*l)->argc) = 1;
		return ;
	}
	len = 0;
	new_argv = (char **) malloc (((*l)->argc+1) * sizeof(char *));
	i = 0;
	while (i < (*l)->argc)
	{
		new_argv[i] = ((*l)->argv)[i];
		i++;
	}
	new_argv[i] = word;
	free((*l)->argv);
	(*l)->argv = new_argv;
	((*l)->argc)++;
}

void init_command(c_list *l)
{
	(*l)->argv = NULL;
	(*l)->argc = 0;
	(*l)->filename = NULL;
}

void add_command_at_end(t_line *line, c_list list)
{
	int		i;
	c_list	aux;

	if (line->ncommands == 0)
	{
		line->commands = list;
		(line->ncommands)++;
		return ;
	}
	aux = (c_list) malloc ((line->ncommands+1) * sizeof(t_command));
	i = 0;
	while (i < line->ncommands)
	{
		aux[i] = (line->commands)[i];
		i++;
	}
	aux[i] = *list;
	free(line->commands);
	line->commands = aux;
	(line->ncommands)++;
}