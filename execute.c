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

void	exec_builtin(char *argv, char **command, char **env)
{
	if (ft_strncmp(argv, "echo", 5) == 0)
	{
		builtin_echo(argv, command, env);
	}
	else if (ft_strncmp(argv, "cd", 3) == 0)
	{
		builtin_cd(argv, command, env);
	}
	else if (ft_strncmp(argv, "pwd", 4) == 0)
	{
		builtin_pwd(argv, command, env);
	}
	// else if (ft_strncmp(argv[0], "export", 7) == 0)
	// {
	// 	builtin_export(argv, command, env);
	// }
	// else if (ft_strncmp(argv[0], "unset", 6) == 0)
	// {
	// 	builtin_unset(argv, command, env);
	// }
	else if (ft_strncmp(argv, "env", 4) == 0)
	{
		builtin_env(argv, command, env);
	}
	else if (ft_strncmp(argv, "exit", 5) == 0)
	{
		exit(0);
	}
}

void execute_builtin(char **argv, int argc, char **env)
{
	int		fd[2];
	char	**command;
	int		i;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	command = (char **) malloc ((argc+1) * sizeof(char *));
	i = 0;
	while (i < argc)
	{
		command[i] = argv[i];
		i++;
	}
	command[i] = NULL;
	exec_builtin(argv[0], command, env);
	close(STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}

void	pipex(char **argv, int argc, char **env)
{
	int		fd[2];
	pid_t	pid;
	char	**command;
	int		i;
	int		status;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		command = (char **) malloc ((argc+1) * sizeof(char *));
		i = 0;
		while (i < argc)
		{
			command[i] = argv[i];
			i++;
		}
		command[i] = NULL;
		execve(argv[0], command, env);
		exit(0);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		waitpid(pid, &status, 0);
	}
}

void execute_commands(t_line *line, char **env)
{
    int infd;
	int outfd;
	int	fd;
	int	i;
	char *str;

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
			execute_builtin(line->commands[i].argv, line->commands[i].argc, env);
		else
			pipex(line->commands[i].argv, line->commands[i].argc, env);
		i++;
	}
	fd = outfd;
    if (line->redirect_output != NULL)
	{
		fd = open(line->redirect_output, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd < 0)
			perror("Error opening outfile");
	}
	//
	//read(STDIN_FILENO, buf, 1) != 0
	char buf[6];
	while(str = get_next_line(STDIN_FILENO))
	{
		write(fd, str, ft_strlen(str));
	}
	dup2(infd, STDIN_FILENO);
	close(infd);
	dup2(outfd, STDOUT_FILENO);
	close(outfd);
}
