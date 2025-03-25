/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_and_routes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssousmat <ssousmat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:13:53 by ssousmat          #+#    #+#             */
/*   Updated: 2025/03/17 18:31:29 by ssousmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_protected(char *str1, char *str2)
{
	char	*res;

	res = ft_strjoin(str1, str2);
	if (!res)
	{
		ft_printf_2("minishell: memory error\n");
		exit(EXIT_FAILURE);
	}
	return (res);
}

char	*ft_strdup_protected(char *str)
{
	char	*res;

	res = ft_strdup(str);
	if (!res)
	{
		ft_printf_2("minishell: memory error\n");
		exit(EXIT_FAILURE);
	}
	return (res);
}

char	**get_path(char **env)
{
	size_t	i;
	char	**div_path;

	i = 0;
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			div_path = ft_split(env[i] + 5, ':');
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
	while (div_path[i])
	{
		temp = ft_strjoin_protected(div_path[i++], "/");
		cmd_path = ft_strjoin_protected(temp, cmd);
		free(temp);
		if (!access(cmd_path, F_OK))
			return (cmd_path);
		free(cmd_path);
	}
	return (NULL);
}

void	ft_no_such_file(char *cmd)
{
	ft_printf_2("minishell: %s: No such file or directory\n", cmd);
	return (NULL);
}

char	*expand_alias2(char *cmd, char **env)
{
	char	**div_path;
	char	*cmd_path;

	// if (!cmd)
	// {
	// 	ft_printf_2("\'\': command not found\n");
	// 	exit(EXIT_FAILURE);
	// }
	if (is_builtin(cmd))
		return (NULL);
	if ((cmd[0] == '/' || !ft_strncmp("./", cmd, 2) \
		|| !ft_strncmp("../", cmd, 3) || !ft_strncmp("~/", cmd, 2)) \
		&& !access(cmd, F_OK))
		return (ft_strdup_protected(cmd));
	div_path = get_path(env);
	if (div_path)
	{
		cmd_path = ft_cmd_in_path(div_path, cmd);
		if (cmd_path)
			return (ft_free_m(div_path), cmd_path);
	}
	else if (!access(cmd, F_OK))
		return (ft_strdup_protected(cmd));
	else
		ft_no_such_file(cmd);				//	es necesario este caso?
	return (ft_free_m(div_path), NULL);
}
