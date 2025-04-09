/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssousmat <ssousmat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:56:32 by igsanche          #+#    #+#             */
/*   Updated: 2025/04/09 14:06:30 by ssousmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_header(char *env_var)
{
	int		len;
	char	*header;

	len = ft_strchr(env_var, '=') - env_var + 1;
	header = (char *) malloc (len * sizeof(char));
	ft_strlcpy(header, env_var, len);
	return (header);
}

// Gets a header, the env vars, and a pointer to a int
// Returns the value of the var pointed by header, NULL if no var is founded
// If env_num is not NULL, set the pointer to the pos of the var in env 
char	*check_env(char *word, t_minishell *minishell, int *env_num)
{
	int		i;
	char	*header;

	i = 0;
	if (ft_strncmp(word, "?", 2) == 0)
		return (ft_itoa(minishell->exit_value));
	while (minishell->env[i] != NULL)
	{
		header = get_env_header(minishell->env[i]);
		if (ft_strncmp(header, word, ft_strlen(header) + 1) == 0)
		{
			if (env_num != NULL)
				*env_num = i;
			return (free(header),
				ft_strdup(ft_strchr(minishell->env[i], '=') + 1));
		}
		free(header);
		i++;
	}
	return (NULL);
}

bool	true_check_env(char *var_name, t_minishell *mini, int *env_index)
{
	char	*temp;

	temp = check_env(var_name, mini, env_index);
	if (!temp)
		return (false);
	free(temp);
	return (true);
}
