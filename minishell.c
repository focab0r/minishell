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
	len += ft_strlen(user) + ft_strlen(max_path);
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

void	deal_input(char *input, t_minishell *minishell)
{
	int		status;

	if (input)
	{
		if (input[0])
		{
			add_history(input);
			status = parse_input(input, minishell);
			free(input);
			if (status == 1)
			{
				ft_printf("Error: Invalid syntax\n");
				save_exit_value(1, minishell);
			}
			else if (minishell->line->ncommands != 0)
				execute_commands(minishell->line, minishell);
			clean_line(minishell->line);
			minishell->line = NULL;
		}
	}
	else
	{
		clean_all(minishell);
		exit(0);
	}
}

void	free_shelllvl(t_command *command, char *shelllvl_c)
{
	free(command->argv[0]);
	free(command->argv[1]);
	free(command->filename);
	free(command->argv);
	free(command);
	free(shelllvl_c);
}

void	update_shelllvl(t_minishell *mini)
{
	t_command	*command;
	char		*str;
	int			shelllvl;
	char		*shelllvl_c;

	shelllvl_c = check_env("SHLVL", mini, NULL);
	if (shelllvl_c)
	{
		shelllvl = ft_atoi(shelllvl_c) + 1;
		free(shelllvl_c);
	}
	else
		shelllvl = 1;
	shelllvl_c = ft_itoa(shelllvl);
	command = (t_command *) malloc (1 * sizeof(t_command));
	command->argc = 2;
	command->argv = (char **) malloc (2 * sizeof(char *));
	command->filename = ft_strdup("export");
	command->argv[0] = ft_strdup("export");
	str = (char *) ft_calloc((6 + ft_strlen(shelllvl_c)+1), sizeof(char));
	ft_strlcpy(str, "SHLVL=", 7);
	command->argv[1] = str;
	ft_strlcat(str, shelllvl_c, 6 + ft_strlen(shelllvl_c)+1);
	builtin_export(mini, *command);
	free_shelllvl(command, shelllvl_c);
}

int	main(int argc, char **argv, char **env)
{
	char				*input;
	char				*cursor;
	t_minishell			*minishell;

	minishell = init_shell(argc, argv, env);
	update_shelllvl(minishell);
	while (1)
	{
		cursor = get_cursor();
		if (g_signal == 2)
		{
			free(cursor);
			cursor = NULL;
		}
		input = readline(cursor);
		if (g_signal)
			save_exit_value(130, minishell);
		if (cursor)
			free(cursor);
		g_signal = 0;
		deal_input(input, minishell);
	}
}
