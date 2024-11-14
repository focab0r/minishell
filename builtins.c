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

int	is_builtin(char *str)
{
	if (ft_strncmp(str, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(str, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(str, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(str, "export", 7) == 0)
		return (1);
	if (ft_strncmp(str, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(str, "env", 4) == 0)
		return (1);
	if (ft_strncmp(str, "exit", 5) == 0)
		return (1);
	return (0);
}

void	builtin_env(char *argv, char **command, char **env)
{
	int	i;

	i = 1;
	while(env[i])
	{
		ft_printf("%s\n", env[i]);
		i++;
	}
}

void	builtin_echo(char *argv, char **command, char **env)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	while (command[i] != NULL)
	{
		if (ft_strncmp(command[i], "-n", 3) == 0)
			flag = 1;
		else
			ft_printf("%s", command[i]);
		i++;
	}
	if (!flag)
		ft_printf("\n");
}

void	builtin_pwd(char *argv, char **command, char **env)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
       ft_printf("%s\n", cwd);
   	}
   	else
	{
       perror("getcwd() error\n");
	}
}

void	builtin_cd(char *argv, char **command, char **env)
{
	if (command[1] != NULL)
	{
		if (chdir(command[1]))
			ft_printf("Invalid path!\n");
	}
}