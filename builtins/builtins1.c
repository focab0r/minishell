/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssousmat <ssousmat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:56:32 by igsanche          #+#    #+#             */
/*   Updated: 2025/04/09 16:43:37 by ssousmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	builtin_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_printf("%s\n", env[i]);
		i++;
	}
	return (0);
}

int	builtin_echo_aux(char *argv)
{
	int	i;

	if (!argv)
		return (0);
	if (argv[0] != '-')
		return (0);
	i = 1;
	while (argv[i])
	{
		if (argv[i] != 'n')
			return (0);
		i++;
	}
	if (i == 1)
		return (0);
	return (1);
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
		if (builtin_echo_aux(command.argv[i]))
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

size_t	builtin_cd(t_command command, t_minishell *mini)
{
	char	*str;

	if (command.argc > 1)
	{
		if (chdir(command.argv[1]))
			return (write(2, "Invalid path!\n", 14), 1);
	}
	else
	{
		str = check_env("HOME", mini, NULL);
		if (!str)
			return (write(2, "cd: HOME not set\n", 17), 1);
		else if (chdir(str))
			return (write(2, "Invalid path!\n", 14), 1);
		free(str);
	}
	update_pwds(mini);
	return (0);
}
