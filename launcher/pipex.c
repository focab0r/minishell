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

void	pipex_manage_input_append(char *eof, int infd)
{
	int		fd[2];
	char	*buffer;
	int		eof_len;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	eof_len = ft_strlen(eof);
	eof[eof_len] = '\n';
	buffer = get_next_line(infd);
	while (ft_strncmp(buffer, eof, eof_len + 1) != 0)
	{
		write(fd[1], buffer, ft_strlen(buffer));
		free(buffer);
		buffer = get_next_line(infd);
	}
	free(buffer);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}

void	pipex_manage_output(t_command command)
{
	int	aux_fd;

	if (command.redirect_output && !command.append_output)
		aux_fd = open(command.redirect_output, O_CREAT
				| O_RDWR | O_TRUNC, 0644);
	else
		aux_fd = open(command.append_output, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (aux_fd < 0)
	{
		write(2, "Unable to open file\n", 20);
		exit(1);
	}
	dup2(aux_fd, STDOUT_FILENO);
	close(aux_fd);
}

void	pipex_manage_input_redirect(t_command command)
{
	int	aux_fd;

	aux_fd = open(command.redirect_input, O_RDONLY);
	if (aux_fd < 0)
	{
		write(2, "Unable to open file\n", 20);
		exit(1);
	}
	dup2(aux_fd, STDIN_FILENO);
	close(aux_fd);
}

void	init_child(t_command command, int infd, int last_command, int *fd)
{
	signal(SIGQUIT, SIG_DFL);
	if (!last_command)
		dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	if (command.redirect_output || command.append_output)
		pipex_manage_output(command);
	if (command.append_input)
		pipex_manage_input_append(command.append_input, infd);
	else if (command.redirect_input)
		pipex_manage_input_redirect(command);
}

int	pipex(t_command command, t_minishell *minishell, int infd, int last_command)
{
	int		fd[2];
	pid_t	pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		init_child(command, infd, last_command, fd);
		if (command.filename == NULL)
		{
			exec_builtin(command, minishell);
			exit(0);
		}
		else
			execve(command.filename, command.argv, minishell->env);
		exit(42);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		return (pid);
	}
}
