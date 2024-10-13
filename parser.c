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


void pass_till_comma(char *input, int *i)
{
    char	elem;

	elem = input[*i];
	i++;
	while (input[*i] != elem && input[*i])
	{
		(*i)++;
	}
}

int count_commands(char *input)
{
    int     num;
    int     i;
    char    elem;

    num = 0;
    i = 0;
    while (input[i])
    {
        if (input[i] == '|')
            num++;
        if (input[i] == '\'' || input[i] == '"')
            pass_till_comma(input, &i);
        if (input[i])
            i++;
    }
    return (num+1);
}

char	get_word(char *input)
{
	int	i;
	int e;

	i = 0;
	while(input[i] == ' ')
		i++;
	while (input[i] && input[i] != ' ' && input[i] != '|' && input[i] != '<' && input[i] != '>')
	{
		if (input[i] == '\'' || input[i] == '"')
			pass_till_comma(input, &i);
		if (input[i])
			i++;
	}
	if (!input[i])
		exit (1) //Error, las comillas no estan bien cerradas
	ç
}

void save_commands(t_line *line, char *input)
{
    int 		words;
    int 		i;
    int 		counter;
	t_command	*c;

    words = line->ncommands;
    i = 0;
    while(words)
    {
		c = (t_command *) malloc (sizeof(t_command)); //c is not freed
        counter = i;
        while (input[counter] && input[counter] != '<' && input[counter] != '>')
        {
			if (input[i] == '\'' || input[i] == '"')
				pass_till_comma(input, &counter);
            counter++;
        }
		if (counter == i)
			exit(1); // Throw an error and exit
		
        words--;
    }
}

void parse_input(char *input)
{
    t_line line;

    line.background = 0;
    line.redirect_input = NULL;
    line.redirect_output = NULL;
    line.redirect_error = NULL;
    line.commands = NULL;
    line.ncommands = count_commands(input);
    save_commands(&line, input);
}