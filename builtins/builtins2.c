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

void	free_and_null(char **var)
{
	free(*var);
	*var = NULL;
}

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

void	builtin_unset(t_minishell *minishell, t_command command)
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
}

void	builtin_export_aux(t_minishell *minishell, t_command *command, int *len, int i)
{
	int		e;
	char	*header;
	char	*value;

	while (i < command->argc)
	{
		if (ft_strrchr(command->argv[i], '=') && command->argv[i][0] != '=')
		{
			header = get_env_header(command->argv[i]);	//Get header of the var we are checking
			value = check_env(header, minishell, &e);		//Check if the var exists
			if (value && ft_isalpha(header[0]))
			{
				free(value);
				free(minishell->env[e]);
				minishell->env[e] = command->argv[i];
				command->argv[i] = NULL;
			}
			else if(!ft_isalpha(header[0]))				//If the export var doesnt start with a alphachar 
			{
				ft_printf_2("export: \"%s\" not a valid identiifier\n", command->argv[i]);
				command->argv[i] = NULL;
			}
			else
				(*len)++;
			free(header);
		}
		else
			free_and_null(&(command->argv[i]));
		i++;
	}
}

void	builtin_export(t_minishell *minishell, t_command command)
{
	int		i;
	int		e;
	int		len;
	char	**new_env;

	len = 0;
	builtin_export_aux(minishell, &command, &len, 1);
	i = 0;
	while (minishell->env[i])
		i++;
	new_env = (char **) malloc ((i + len + 1) * sizeof(char *));
	new_env[i + len] = NULL;
	i = 0;
	e = 0;
	while (minishell->env[i])
		new_env[i++] = minishell->env[e++];
	e = 1;
	while (e < command.argc)
	{
		if (command.argv[e])
			new_env[i++] = ft_strdup(command.argv[e]);
		e++;
	}
	free(minishell->env);
	minishell->env = new_env;
}
