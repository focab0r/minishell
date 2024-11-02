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

void execute_commands(t_line *line, char **env)
{
    int infd;
	int	fd;
	int	i;
	char *str;

	dup2(STDIN_FILENO, infd);
    if (line->redirect_input != NULL)
	{
		fd = open(line->redirect_input, O_RDONLY);
		if (fd < 0)
			perror("Infile");
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	i = 0;
	while (i < line->ncommands)
	{
		pipex(line->commands[i].argv, line->commands[i].argc, env);
		i++;
	}
	fd = 1;
    if (line->redirect_output != NULL)
	{
		fd = open(line->redirect_output, O_RDWR | O_CREAT);
		if (infd < 0)
			perror("Outfile");
	}
	while(str = get_next_line(STDIN_FILENO))
	{
		write(fd, str, ft_strlen(str));
		free(str);
	}
	dup2(infd, STDIN_FILENO);
    // int i;

    // i = 0;
    // while (i < line->ncommands)
    // {
    //     if (ft_strncmp(line->commands[i].filename, "exit", 5) == 0)
    //         exit(0);
    //     else
    //         exec_command(line->commands[i]);
    //     i++;
    // }
}