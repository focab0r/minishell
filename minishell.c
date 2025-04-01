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

void	init_env(char ***env)
{
	int		i;
	int		e;
	char	**new_env;

	i = 0;
	while ((*env)[i])
		i++;
	new_env = (char **) malloc ((i + 1) * sizeof(char *));
	new_env[i] = NULL;
	e = 0;
	while (e < i)
	{
		new_env[e] = ft_strdup((*env)[e]);
		e++;
	}
	*env = new_env;
}

void	init_shell(int argc, char **argv, char ***env)
{
	(void)argc;
	(void)argv;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	init_env(env);
	save_exit_value(0, env);
	g_signal = 0;
}

void	deal_input(char *input, char ***env)
{
	t_line	*line;
	int		status;

	if (input)
	{
		add_history(input);
		status = parse_input(&line, input, *env);
		free(input);
		if (status == 1)
		{
			ft_printf("Error: Invalid quotes syntax\n");
			save_exit_value(1, env);
		}
		else if (line->ncommands != 0)
			execute_commands(line, env);
		clean_line(line);
	}
	else
		clean_all(NULL, *env);
}

int	main(int argc, char **argv, char **env)
{
	char				*input;
	char				*cursor;

	init_shell(argc, argv, &env);
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
		deal_input(input, &env);
	}
}
