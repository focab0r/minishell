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

void exec_command(t_command c)
{
    int pid;

    pid = fork();
    if (pid == 0)
    {
        execve(c.filename, c.argv, NULL);
    }
}

void execute_commands(t_line *line)
{
    int i;

    i = 0;
    while (i < line->ncommands)
    {
        if (ft_strncmp(line->commands[i].filename, "exit", 5) == 0)
            exit(0);
        else
            exec_command(line->commands[i]);
        i++;
    }
}