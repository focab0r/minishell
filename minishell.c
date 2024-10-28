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

void    save_env(t_minishell *m)
{
    m->PATH = getenv("PATH");
}

int main()
{
    t_minishell m;
    char        *input;
    t_line      *line;

    save_env(&m);
    line = (t_line *) malloc (sizeof(t_line));
    while(1)
    {
        input = readline ("$> ");
        if (input)
        {
            add_history(input);
            parse_input(line, input);
            replace_vars(m, line);
            escape_quotes(line);
            expand_alias(m, line);
            //print_line(line);
        }
    }
}