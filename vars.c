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

char    *find_vars(char *command)
{
	int		i;
	char	*start;
	char	*end;

	i = 0;
	while(command[i])
	{
		if (command[i] == '\'')
		{
			i++;
			while(command[i] == '\'')
				i++;
		}
		if (command[i] == '$')
		{
			start = &(command[i]);
			i++;
			while(command[i] && ft_isalnum(command[i]))
				i++;
			end = &(command[i]);
			if (start != end)
				end--;
			//llamda a funcion, start y end ahora tienen los punteros al  inicio y final de variable
		}
		i++;
	}
}

void replace_vars(t_minishell m, t_line *line)
{
    int i;

    i = 0;
    while (i < line->ncommands)
    {
        find_vars(line->commands[i].filename);
        i++;
    }
       
}