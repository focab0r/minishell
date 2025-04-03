/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssousmat <ssousmat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:56:32 by igsanche          #+#    #+#             */
/*   Updated: 2025/04/02 15:26:16 by ssousmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

char	*get_cursor(void)
{
	char	*user;
	char	max_path[PATH_MAX];
	int		len;
	char	*str;

	user = getenv("USER");
	if (user == NULL)
		user = "unknown";
	getcwd(max_path, sizeof(max_path));
	len = 0;
	len += ft_strlen(user);
	len += ft_strlen(max_path);
	len += 11;
	len += sizeof(GREEN) + sizeof(RESET);
	len += sizeof(BLUE) + sizeof(RED) + sizeof(MAGENTA);
	str = (char *) malloc (len * sizeof(char));
	ft_strlcpy(str, GREEN, ft_strlen(GREEN) + 1);
	ft_strlcpy(str + ft_strlen(str), user, ft_strlen(user) + 1);
	ft_strlcpy(str + ft_strlen(str), BLUE, ft_strlen(BLUE) + 1);
	ft_strlcpy(str + ft_strlen(str), " [at] ", 7);
	ft_strlcpy(str + ft_strlen(str), MAGENTA, ft_strlen(MAGENTA) + 1);
	ft_strlcpy(str + ft_strlen(str), max_path, ft_strlen(max_path) + 1);
	ft_strlcpy(str + ft_strlen(str), RED, ft_strlen(RED) + 1);
	ft_strlcpy(str + ft_strlen(str), " $> ", 5);
	ft_strlcpy(str + ft_strlen(str), RESET, ft_strlen(RESET) + 1);
	return (str);
}

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
	return new_env;
}

t_minishell	*init_shell(int argc, char **argv, char **env)
{
	t_minishell *minishell;

	minishell = (t_minishell *) malloc (1*sizeof(t_minishell));
	(void)argc;
	(void)argv;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	env = init_env(env);
	minishell->env = env;
	save_exit_value(0, minishell);
	g_signal = 0;
	return minishell;
}

void	deal_input(char *input, t_minishell *minishell)
{
	t_line	*line;
	int		status;

	if (input)
	{
		add_history(input);
		status = parse_input(&line, input, minishell);
		minishell->line = line;
		free(input);

		if (status == 1)
		{
			ft_printf("Error: Invalid syntax\n");
			save_exit_value(1, minishell);
		}
		else if (line->ncommands != 0)
			execute_commands(line, minishell);
		clean_line(minishell->line);
	}
	else
		clean_all(NULL, minishell->env);
}

int	main(int argc, char **argv, char **env)
{
	char				*input;
	char				*cursor;
	t_minishell			*minishell;

	minishell = init_shell(argc, argv, env);
	while (1)
	{
		cursor = get_cursor();
		if (g_signal == 2)
		{
			free(cursor);
			cursor = NULL;
		}
		input = readline(cursor);
		if (cursor)
			free(cursor);
		g_signal = 0;
		deal_input(input, minishell);
	}
}
