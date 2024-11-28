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

void	builtin_cd(char *argv, char **command)
{
	if (command[1] != NULL)
	{
		if (chdir(command[1]))
			printf("Invalid path!\n");
	}
}