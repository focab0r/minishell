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

char	*concat_word(char *command, char *start, char *end, char *var)
{
	int		len;
	char	*str;
	int		i;

	len = start - command;
	len += ft_strlen(var);
	len += ft_strlen(end+1);
	str = (char *) malloc ((len+1)*sizeof(char));
	i = 0;
	while (command != start)
	{
		str[i] = *command;
		command++;
		i++;
	}
	while (*var)
	{
		str[i] = *var;
		var++;
		i++;
	}
	end++;
	while(*end)
	{
		str[i] = *end;
		end++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

int sustitute_word(char **command, char *start, char *end)
{
	char	*var;
	char	*word;
	char	*str;
	int		len;
	int		i;

	len = end - start + 1;
	word = (char *) malloc ((len+1)*sizeof(char));
	ft_strlcpy(word, start, len+1);
	//var = check_env(word);
	//if (var == NULL)
		var = getenv(word+1);
	if (var == NULL)
	{
		var = (char *) malloc (1*sizeof(char));
		var[0] = '\0';
	}
	str = concat_word(*command, start, end, var);
	i = start - *command + ft_strlen(var) - 1;
	free(*command);
	//free(var);
	*command = str;
	return(i);
}

char    *find_vars(char *command)
{
	int		i;
	char	*start;
	char	*end;
	char	*str;
	i = 0;
	while(command[i])
	{
		if (command[i] == '\'')
		{
			i++;
			while(command[i] != '\'')
				i++;
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
				i = sustitute_word(&command, start, end);
		}
		i++;
	}
	return (command);
}

void replace_vars(t_minishell m, t_line *line)
{
    int 	i;
	char	*str;

    i = 0;
    while (i < line->ncommands)
    {
        str = find_vars(line->commands[i].filename);
		line->commands[i].filename = str;
        i++;
    }
       
}