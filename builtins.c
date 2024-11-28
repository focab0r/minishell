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

int	is_builtin(char *str)
{
	if (strncmp(str, "cd", 3) == 0)
		return (1);
	if (strncmp(str, "exit", 5) == 0)
		return (1);
	return (0);
}

void	builtin_cd(tcommand t)
{
	if (t.argc > 1)
	{
		if (chdir(t.argv[1]))
			printf("Invalid path!\n");
	}
}

void	builtin_jobs(tcommand t, twaitpid *pid_stock)
{
	int i;

	i = 0;
	while (i < pid_stock->background_commands)
	{
		printf("%d\n", pid_stock->background_commands);
		print_line(pid_stock->lines[i]);
		if(!check_if_line_is_dead(pid_stock->lines[i], pid_stock->waitpid_estructure[i]))
		{
			printf("- %d\n", i);
			show_line_as_jobs(i, pid_stock->lines[i]);
		}
		else
		{
			//delete_line_as_jobs();
		}
		i++;
	}
}

void	builtin_fg(tcommand t, twaitpid *pid_stock)
{

}