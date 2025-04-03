/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssousmat <ssousmat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:56:32 by igsanche          #+#    #+#             */
/*   Updated: 2025/04/02 22:44:08 by ssousmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	builtin_env(char **env)
{
	int	i;

	i = 1;
	while (env[i])
	{
		ft_printf("%s\n", env[i]);
		i++;
	}
	return (0);
}

size_t	builtin_echo(t_command command)
{
	int	i;
	int	flag;
	int	flag2;

	i = 1;
	flag = 0;
	flag2 = 0;
	while (i < command.argc)
	{
		if (ft_strncmp(command.argv[i], "-n", 3) == 0)
			flag = 1;
		else
		{
			if (flag2)
				ft_printf(" ");
			ft_printf("%s", command.argv[i]);
			flag2 = 1;
		}
		i++;
	}
	if (flag == 0)
		ft_printf("\n");
	return (0);
}

size_t	builtin_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_printf("%s\n", cwd);
	else
	{
		perror("getcwd");
		return (1);
	}
	return (0);
}

size_t	builtin_cd(t_command command)
{
	if (command.argc > 1)
	{
		if (chdir(command.argv[1]))
		{
			write(2, "Invalid path!\n", 14);
			return(1);
		}
	}
	else
	{
		if (chdir(getenv("HOME")))
		{
			write(2, "Invalid path!\n", 14);
			return(1);
		}
	}
	return (0);
}
