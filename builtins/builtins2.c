/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssousmat <ssousmat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:56:32 by igsanche          #+#    #+#             */
/*   Updated: 2025/04/01 20:55:32 by ssousmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_and_null(char **var)
{
	free(*var);
	*var = NULL;
}

void	builtin_unset_aux(char ***env, t_command command, int *len)
{
	int		i;
	int		e;
	char	*header;

	i = 0;
	while (i < command.argc)
	{
		header = check_env(command.argv[i], *env, &e);
		if (header)
		{
			(*len)++;
			free(header);
			free_and_null(&((*env)[e]));
		}
		i++;
	}
}

size_t	builtin_unset(char ***env, t_command command)
{
	int		i;
	int		e;
	int		len;
	int		env_len;
	char	**new_env;

	env_len = 0;
	i = 0;
	while ((*env)[i++])
		env_len++;
	len = 0;
	builtin_unset_aux(env, command, &len);
	new_env = (char **) malloc ((env_len - len + 1) * sizeof(char *));
	new_env[env_len - len] = NULL;
	i = 0;
	e = 0;
	while (i < env_len)
	{
		if ((*env)[i])
			new_env[e++] = (*env)[i];
		i++;
	}
	free(*env);
	*env = new_env;
	return (0);
}

void	builtin_export_aux(char ***env, t_command *command, int *len, int i)
{
	int		e;
	char	*header;
	char	*value;

	while (i < command->argc)
	{
		if (ft_strrchr(command->argv[i], '=') && command->argv[i][0] != '=')
		{
			header = get_env_header(command->argv[i]);
			value = check_env(header, *env, &e);
			free(header);
			if (value)
			{
				free(value);
				free((*env)[e]);
				(*env)[e] = command->argv[i];
				command->argv[i] = NULL;
			}
			else
				(*len)++;
		}
		else
			free_and_null(&(command->argv[i]));
		i++;
	}
}

size_t	builtin_export(char ***env, t_command command)
{
	int		i;
	int		e;
	int		len;
	char	**new_env;

	len = 0;
	builtin_export_aux(env, &command, &len, 1);
	i = 0;
	while ((*env)[i])
		i++;
	new_env = (char **) malloc ((i + len + 1) * sizeof(char *));
	new_env[i + len] = NULL;
	i = 0;
	e = 0;
	while ((*env)[i])
		new_env[i++] = (*env)[e++];
	e = 1;
	while (e < command.argc)
	{
		if (command.argv[e])
			new_env[i++] = ft_strdup(command.argv[e]);
		e++;
	}
	free(*env);
	*env = new_env;
	return (0);
}
