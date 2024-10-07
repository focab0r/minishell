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

    save_env(&m);
    while(1)
    {
        input = readline ("$> ");
        ft_printf("You'v entered: %s\n", input);
        if (input)
        {
            add_history(input);
            parse_input(input);
        }
    }
}