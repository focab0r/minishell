/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protected.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssousmat <ssousmat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:56:58 by ssousmat          #+#    #+#             */
/*   Updated: 2025/04/02 21:15:59 by ssousmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_fork_protected(pid_t *pid, t_minishell *mini)
{
	*pid = fork();
	if (*pid == -1)
	{
		perror("minishell: fork");
		exit(EXIT_FAILURE);
	}
}

void	ft_pipe_protected(int *pipefd, t_minishell *mini)
{
	if (pipe(pipefd) == -1)
	{
		perror("minishell: pipe");
		exit(EXIT_FAILURE);
	}
}

void	ft_dup2_protected(int fd1, int fd2, t_minishell *mini)
{
	if (dup2(fd1, fd2) == -1)
	{
		if (fd1 >= 3)
			close(fd1);
		perror("minishell: dup2");
		exit(EXIT_FAILURE);
	}
}
