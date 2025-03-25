/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssousmat <ssousmat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:12:55 by ssousmat          #+#    #+#             */
/*   Updated: 2025/03/25 19:50:59 by ssousmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_command(t_line *line, int *i)
{
	if (line->commands[*i].argv[1])
	{
		if (!ft_isnum(line->commands[*i].argv[1]))
		{
			ft_printf_2("minishell: exit: %s: numeric argument required\n", \
						line->commands[*i].argv[1]);
			exit(2);
		}
		else if (line->commands[*i].argv[2])
		{
			ft_printf_2("minishell: exit: too many arguments\n");
			if (line->ncommands == 1)
				return ;												// codigo de salida = 1
			exit(1);
		}
		exit(ft_atoi((const char)line->commands[*i].argv[1]));
	}
	else
		exit(0);
}

void	builtin_exit(t_line *line, int *i)
{
	if (line->ncommands != 1)
	{
		line->commands[*i].pid = ft_fork_protected();
		if (!line->commands[*i].pid)
			exit_command(line, i);
	}
	else
	{
		ft_printf_2("exit\n");
		exit_command(line, i);
	}
}