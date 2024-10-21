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

int is_alias(char *command)
{
	if (command[0] == '/')
		return (0);
	if (command[0] == '.')
		return (0);
}

int	check_if_file_is_exec(char *command)
{
	if(access(command, X_OK) == 0)
		return (1);
	return (0);
}

char	*check_command_in_path(char *command, char **path)
{
	int		i;
	char	*str;
	int		len;
	int		command_len;

	i = 0;
	command_len = ft_strlen(command);
	while (path[i])
	{
		len = ft_strlen(path[i]) + command_len + 1;
		str = (char *) malloc ((len + 1) * sizeof(char));
		ft_strlcpy(str, path[i], len+1);
		ft_strlcat(str, "/", len+1);
		ft_strlcat(str, command, len+1);
		if(check_if_file_is_exec(str))
			return (str);
		i++;
	}
	ft_printf("Error: %s not found\n", command);
	return (NULL);
}

void expand_alias(t_minishell m, t_line *line)
{
    char    **path;
    char	*command;
    int     i;
    int     e;

    path = ft_split(m.PATH, ':');
    i = 0;
    while (i < line->ncommands)
    {
		command = line->commands[i].filename;
		if (is_alias(command))
		{
			command = check_command_in_path(command, path);
			if (command != NULL)
			{
				free(line->commands[i].filename);
				line->commands[i].filename = command;
			}
		}
		else
		{
			if(!check_if_file_is_exec(command))
				ft_printf("Error: %s not found\n", command);
		}
		i++;
    }

}

int	calc_quotes_len(char *str)
{
	int		i;
	char	quote;
	int		len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			quote = str[i];
			i++;
			while (str[i] != quote)
			{
				len++;
				i++;
			}
		}
		else
			len++;
		i++;
	}
	return (len);
}

char	*transform_quotes(char *str)
{
	int		len;
	char	*new_str;
	int		i;
	char	quote;

	len = calc_quotes_len(str);
	new_str = (char *) malloc ((len + 1) * sizeof(char));
	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			quote = str[i];
			i++;
			while (str[i] != quote)
			{
				new_str[len] = str[i];
				len++;
				i++;
			}
		}
		else
		{
			new_str[len] = str[i];
			len++;
		}
		i++;
	}
	new_str[len] = '\0';
	return (new_str);
}

void	escape_quotes(t_line *line)
{
	int		i;
	int		e;
	char	*str;
	char	*new_str;

	i = 0;
	while (i < line->ncommands)
    {
		str = line->commands[i].filename;
		new_str = transform_quotes(str);
		free(str);
		line->commands[i].filename = new_str;
		e = 0;
		while (e < line->commands[i].argc)
		{
			str = line->commands[i].argv[e];
			new_str = transform_quotes(str);
			free(str);
			line->commands[i].argv[e] = new_str;
			e++;
		}
		i++;
    }
}