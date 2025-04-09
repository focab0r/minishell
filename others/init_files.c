/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssousmat <ssousmat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:56:32 by igsanche          #+#    #+#             */
/*   Updated: 2025/04/08 17:43:46 by ssousmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**init_env(char **env)
{
	int		i;
	int		e;
	char	**new_env;

	i = 0;
	while (env[i])
		i++;
	new_env = (char **) malloc ((i + 1) * sizeof(char *));
	new_env[i] = NULL;
	e = 0;
	while (e < i)
	{
		new_env[e] = ft_strdup(env[e]);
		e++;
	}
	return (new_env);
}

t_minishell	*init_shell(int argc, char **argv, char **env)
{
	t_minishell	*minishell;

	minishell = (t_minishell *) malloc (1 * sizeof(t_minishell));
	(void)argc;
	(void)argv;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	env = init_env(env);
	minishell->env = env;
	minishell->line = NULL;
	save_exit_value(0, minishell);
	g_signal = 0;
	return (minishell);
}
