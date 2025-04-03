/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssousmat <ssousmat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:13:53 by ssousmat          #+#    #+#             */
/*   Updated: 2025/04/02 21:30:30 by ssousmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_protected(char *str1, char *str2, t_minishell *mini)
{
	char	*res;

	res = ft_strjoin(str1, str2);
	if (!res)
	{
		ft_printf_2("minishell: memory error\n");
		exit(EXIT_FAILURE);							//liberar memoria
	}
	return (res);
}

char	*ft_strdup_protected(char *str, t_minishell *mini)
{
	char	*res;

	res = ft_strdup(str);
	if (!res)
	{
		ft_printf_2("minishell: memory error\n");
		exit(EXIT_FAILURE);							//liberar memoria
	}
	return (res);
}

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

char	*ft_cmd_in_path(char **div_path, char *cmd, t_minishell *mini)
{
	char	*temp;
	char	*cmd_path;
	size_t	i;

	i = 0;
	if (is_builtin(cmd))
		return (NULL);
	while (div_path[i])
	{
		temp = ft_strjoin_protected(div_path[i++], "/", mini);
		cmd_path = ft_strjoin_protected(temp, cmd, mini);
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

	// if (!cmd)
	// {
	// 	ft_printf_2("\'\': command not found\n");
	// 	exit(EXIT_FAILURE);
	// }
	if (is_builtin(cmd))
		return (ft_strdup(cmd));
	if ((cmd[0] == '/' || !ft_strncmp("./", cmd, 2) \
		|| !ft_strncmp("../", cmd, 3) || !ft_strncmp("~/", cmd, 2)) \
		&& !access(cmd, F_OK))
		return (ft_strdup_protected(cmd, mini));
	div_path = get_path(mini);
	if (div_path)
	{
		cmd_path = ft_cmd_in_path(div_path, cmd, mini);
		if (cmd_path)
			return (ft_free_m(div_path), cmd_path);
	}
	else if (!access(cmd, F_OK))
		return (ft_strdup_protected(cmd, mini));
	else
		return(ft_printf_2("minishell: %s: No such file or directory\n", cmd), NULL);				//	es necesario este caso?
	return (ft_free_m(div_path), NULL);
}
