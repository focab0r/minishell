/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssousmat <ssousmat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:13:53 by ssousmat          #+#    #+#             */
/*   Updated: 2025/04/09 12:27:08 by ssousmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_path(t_minishell *mini)
{
	size_t	i;
	char	**div_path;

	i = 0;
	while (mini->env && mini->env[i])
	{
		if (!ft_strncmp(mini->env[i], "PATH=", 5))
		{
			div_path = ft_split(mini->env[i] + 5, ':');
			if (!div_path)
			{
				ft_printf_2("minishell: memory error\n");
				exit(EXIT_FAILURE);
			}
			return (div_path);
		}
		i++;
	}
	return (NULL);
}

char	*ft_cmd_in_path(char **div_path, char *cmd)
{
	char	*temp;
	char	*cmd_path;
	size_t	i;

	i = 0;
	if (is_builtin(cmd))
		return (NULL);
	while (div_path[i])
	{
		temp = ft_strjoin(div_path[i++], "/");
		cmd_path = ft_strjoin(temp, cmd);
		free(temp);
		if (!access(cmd_path, F_OK))
			return (cmd_path);
		free(cmd_path);
	}
	return (NULL);
}

char	*expand_alias(char *cmd, t_minishell *mini)
{
	char	**div_path;
	char	*cmd_path;

	if (is_builtin(cmd))
		return (ft_strdup(cmd));
	if ((cmd[0] == '/' || !ft_strncmp("./", cmd, 2) \
		|| !ft_strncmp("../", cmd, 3) || !ft_strncmp("~/", cmd, 2)) \
		&& !access(cmd, F_OK))
		return (ft_strdup(cmd));
	div_path = get_path(mini);
	if (div_path)
	{
		cmd_path = ft_cmd_in_path(div_path, cmd);
		if (cmd_path)
			return (ft_free_m(div_path), cmd_path);
	}
	else if (!access(cmd, F_OK))
		return (ft_strdup(cmd));
	else
		return(NULL);
	return (ft_free_m(div_path), NULL);
}
