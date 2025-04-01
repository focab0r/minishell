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

int	check_if_file_is_exec(char *command)
{
	if (access(command, X_OK) == 0)
		return (1);
	return (0);
}

char	*check_command_in_path(char *word, char **path)
{
	int		i;
	char	*str;
	int		len;
	int		word_len;

	if (check_if_file_is_exec(word))
		return (ft_strdup(word));
	if (is_builtin(word))
		return (NULL);
	i = 0;
	word_len = ft_strlen(word);
	while (path[i])
	{
		len = ft_strlen(path[i]) + word_len + 1;
		str = (char *) malloc ((len + 1) * sizeof(char));
		ft_strlcpy(str, path[i], len + 1);
		ft_strlcat(str, "/", len + 1);
		ft_strlcat(str, word, len + 1);
		if (check_if_file_is_exec(str))
			return (str);
		free(str);
		i++;
	}
	return (NULL);
}

char	*expand_alias(char *word, t_minishell *minishell)
{
	char	*path;
	char	**complete_path;
	char	*new_word;
	int		i;

	path = check_env("PATH", minishell, NULL);
	if (!path)
		return (NULL);
	complete_path = ft_split(path, ':');
	new_word = check_command_in_path(word, complete_path);
	i = 0;
	while (complete_path[i])
	{
		free(complete_path[i]);
		i++;
	}
	free(path);
	free(complete_path);
	return (new_word);
}
