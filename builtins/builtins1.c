/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssousmat <ssousmat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:56:32 by igsanche          #+#    #+#             */
/*   Updated: 2025/04/08 16:26:41 by ssousmat         ###   ########.fr       */
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
		return 0;
	if (argv[0] != '-')
		return 0;
	i = 1;
	while (argv[i])
	{
		if (argv[i] != 'n')
			return 0;
		i++;
	}
	if (i == 1)
		return 0;
	return 1;
	
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
	char	oldpwd[PATH_MAX];
	char	*str;

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
		str = check_env("HOME", mini, NULL);
		if (!str)
		{
			write(2, "cd: HOME not set\n", 17);
			return (1);
		}
		else if (chdir(str))
		{
			write(2, "Invalid path!\n", 14);
			return(1);
		}
		free(str);
	}
	update_pwds(mini);
	return (0);
}

// void	add_to_env(char *var, t_minishell *mini)
// {
// 	int		i;
// 	char	**new_env;

// 	i = 0;
// 	while (mini->env[i])
// 		i++;
// 	new_env = (char **) malloc ((i + 2) * sizeof(char *));
// 	if (!new_env)
// 		exit(EXIT_FAILURE);
// 	new_env[i + 1] = NULL;
// 	i = 0;
// 	while (mini->env[i])
// 		new_env[i] = mini->env[i++];
// 	new_env[i] = ft_strdup_protected(var, mini);
// 	free(mini->env);
// 	mini->env = new_env;
// }


// PWD_flag = 1;
// size_t builtin_cd(t_command command, t_minishell *mini)
// {
// 	char 		pwd[PATH_MAX];
// 	char		*pwd_env;
// 	char 		*oldpwd;

// 	pwd_env = check_env("PWD", mini, NULL);
// 	if (!pwd_env && mini->PWD_flag == 0)
// 		oldpwd = getcwd(NULL, 0);
// 	else
// 		oldpwd = pwd_env;
// 	if (pwd_env)
// 		mini->PWD_flag = true;
// 	else
// 		mini->PWD_flag = false;
// 	if (pwd_env)
// 		free(pwd_env);
// 	if (!oldpwd)
// 		return (perror("cd: getcwd"), 1);
	
// 	if (command.argc > 1)
// 		if (chdir(command.argv[1]))
// 			return (free(oldpwd), write(2, "Invalid path!\n", 14), 1);
// 	else
// 		if (chdir(getenv("HOME")))
// 			return (free(oldpwd), write(2, "Invalid path! Home not set\n", 27), 1);

// 	if (!getcwd(pwd, sizeof(pwd)))
// 		return (perror("cd: getcwd"), 1);
// 	update_env_var("OLDPWD", oldpwd, mini);
// 	free(oldpwd);
// 	update_env_var("PWD", pwd, mini);
// 	return (0);
// }
