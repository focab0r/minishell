/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopez-a <plopez-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:04:28 by plopez-a          #+#    #+#             */
/*   Updated: 2023/08/03 17:54:37 by plopez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	get_path(char **env, t_data *data)
{
	int	i;

	data->is_path = 0;
	i = 0;
	while (env[i] && !data->is_path)
	{
		if (ft_strnstr(env[i], "PATH=", 5))
			data->is_path = 1;
		else
			i++;
	}
	if (data->is_path)
	{
		data->path = ft_split(env[i] + 5, ':');
	}
}

char	*get_command(char *command, t_data *data)
{
	int		i;
	char	*aux_com;
	char	*absolute_path;

	i = 0;
	if (data->is_path)
	{
		while (data->path[i])
		{
			aux_com = ft_strjoin(data->path[i], "/");
			absolute_path = ft_strjoin(aux_com, command);
			free(aux_com);
			if (!access(absolute_path, X_OK))
				return (absolute_path);
			i++;
		}
	}
	return (command);
}

void	pipex(char *argv, char **env, t_data *data)
{
	int		fd[2];
	pid_t	pid;
	char	**command;
	char	*path;

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
		command = ft_split(argv, ' ');
		path = get_command(command[0], data);
		if (access(path, F_OK) == -1)
		{
			perror(path);
			exit(EXIT_FAILURE);
		}
		else if (access(path, X_OK) == -1)
		{
			perror(path);
			exit(EXIT_FAILURE);
		}
		execve(path, command, env);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		waitpid(pid, NULL, 0);
	}
}

void	last(char *argv, char **env, t_data *data, int outfd)
{
	pid_t	pid;
	char	**command;
	char	*path;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		dup2(outfd, STDOUT_FILENO);
		close(outfd);
		command = ft_split(argv, ' ');
		path = get_command(command[0], data);
		if (access(path, F_OK) == -1)
		{
			perror(path);
			exit(EXIT_FAILURE);
		}
		else if (access(path, X_OK) == -1)
		{
			perror(path);
			exit(EXIT_FAILURE);
		}
		execve(path, command, env);
	}
	else
	{
		close(outfd);
		waitpid(pid, NULL, 0);
	}
}

void	ft()
{
	system("leaks pipex");
}

int	ft_pipe(int argc, char **argv, char **env)
{
	t_data	data;
	int		i;
	int		infd;
	int		outfd;

	//atexit(ft);
	if (argc < 4)
		exit(EXIT_FAILURE);
	i = 2;
	get_path(env, &data);
	infd = open(argv[1], O_RDONLY);
	if (infd < 0)
		perror("Infile");
	outfd = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (outfd < 0)
		perror("Oufile");
	dup2(infd, STDIN_FILENO);
	close(infd);
	while (i < argc - 2)
		pipex(argv[i++], env, &data);
	last(argv[i], env, &data, outfd);
	i = -1;
	if (data.is_path)
	{
		while (data.path[++i])
			free(data.path[i]);
		free(data.path);
	}
	return (0);
}
