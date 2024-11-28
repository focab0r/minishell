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

void	exec_builtin(char *argv, char **command)
{
	if (strncmp(argv, "cd", 3) == 0)
	{
		builtin_cd(argv, command);
	}
	else if (strncmp(argv, "exit", 5) == 0)
	{
		exit(0);
	}
}

int	pipex(char **argv, int argc, int last_command, char *output_file)
{
	int		fd[2];
	pid_t	pid;
	char	**command;
	int		i;
	int		last_fd;

	if (last_command)
	{
		if (output_file)
		{
			last_fd = open(output_file, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (last_fd < 0)
				perror("Error opening outfile");
		}
		else
			last_fd = 1;
	}
	else
	{
		if (pipe(fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (last_command && last_fd != 1)
		{
			dup2(last_fd, STDOUT_FILENO);
			close(last_fd);
		}
		else if (!last_command)
		{
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
		}
		command = (char **) malloc ((argc+1) * sizeof(char *));
		i = 0;
		while (i < argc)
		{
			command[i] = argv[i];
			i++;
		}
		command[i] = NULL;
		execvp(argv[0], command);
		exit(42);
	}
	else
	{
		if (last_command && last_fd != 1)
			close(last_command);
		else if (!last_command)
		{
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
		}
		return (pid);
	}
}

void execute_commands(tline *line)
{
    int infd;
	int outfd;
	int	fd;
	int	i;
	char *str;
	int *waitpid_list;
	int	status;

	waitpid_list = (int *) calloc (line->ncommands, sizeof(int));

	infd = dup(STDIN_FILENO);
	outfd = dup(STDOUT_FILENO);
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
		if (is_builtin(line->commands[i].filename))
			exec_builtin(line->commands[i].argv[0], line->commands[i].argv);
		else if (line->ncommands - 1 == i) //If it is the last command
			waitpid_list[i] = pipex(line->commands[i].argv, line->commands[i].argc, 1, line->redirect_output);
		else
			waitpid_list[i] = pipex(line->commands[i].argv, line->commands[i].argc, 0, NULL);
		i++;
	}
	if (!line->background)
	{
		i = 0;
		while (i < line->ncommands)
		{
			if (waitpid_list[i])
				waitpid(waitpid_list[i], &status, 0);
			i++;
		}
	}
	dup2(infd, STDIN_FILENO);
	close(infd);
}
