/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssousmat <ssousmat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:56:32 by igsanche          #+#    #+#             */
/*   Updated: 2025/04/09 17:15:57 by ssousmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_unset_aux(t_minishell *minishell, t_command command, int *len)
{
	int		i;
	int		e;
	char	*header;

	i = 0;
	while (i < command.argc)
	{
		header = check_env(command.argv[i], minishell, &e);
		if (header)
		{
			(*len)++;
			free(header);
			free_and_null(&(minishell->env[e]));
		}
		i++;
	}
}

size_t	builtin_unset(t_minishell *minishell, t_command command)
{
	int		i;
	int		e;
	int		len;
	int		env_len;
	char	**new_env;

	env_len = 0;
	i = 0;
	while (minishell->env[i++])
		env_len++;
	len = 0;
	builtin_unset_aux(minishell, command, &len);
	new_env = (char **) malloc ((env_len - len + 1) * sizeof(char *));
	new_env[env_len - len] = NULL;
	i = 0;
	e = 0;
	while (i < env_len)
	{
		if (minishell->env[i])
			new_env[e++] = minishell->env[i];
		i++;
	}
	free(minishell->env);
	minishell->env = new_env;
	return (0);
}

int	salmon(t_command *cmd, t_minishell *mini, int *len, int i)
{
	char	*value;
	char	*header;
	int		e;
	int		exit_code;

	exit_code = 0;
	header = get_env_header(cmd->argv[i]);
	value = check_env(header, mini, &e);
	if (value && ft_isalpha(header[0]))
	{
		free(value);
		free(mini->env[e]);
		mini->env[e] = cmd->argv[i];
		cmd->argv[i] = NULL;
	}
	else if (!ft_isalpha(header[0]))
	{
		ft_printf_2("export: \"%s\" not a valid identifier\n", cmd->argv[i]);
		free(cmd->argv[i]);
		cmd->argv[i] = NULL;
		exit_code = 1;
	}
	else
		(*len)++;
	return (free(header), exit_code);
}

int	builtin_export_aux(t_minishell *minishell, t_command *cmd, int *len, int i)
{
	int		exit_code;

	exit_code = 0;
	while (i < cmd->argc)
	{
		if (ft_strrchr(cmd->argv[i], '=') && cmd->argv[i][0] != '=')
			exit_code = salmon(cmd, minishell, len, i);
		else
			free_and_null(&(cmd->argv[i]));
		i++;
	}
	return (exit_code);
}

size_t	builtin_export(t_minishell *minishell, t_command command)
{
	int		i;
	int		e;
	int		len;
	char	**new_env;
	int		exit_code;

	len = 0;
	exit_code = builtin_export_aux(minishell, &command, &len, 1);
	i = 0;
	while (minishell->env[i])
		i++;
	new_env = (char **) malloc ((i + len + 1) * sizeof(char *));
	new_env[i + len] = NULL;
	i = 0;
	e = 0;
	while (minishell->env[i])
		new_env[i++] = minishell->env[e++];
	e = 0;
	while (++e < command.argc)
		if (command.argv[e])
			new_env[i++] = ft_strdup(command.argv[e]);
	free(minishell->env);
	minishell->env = new_env;
	return (exit_code);
}
