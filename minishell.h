/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igsanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:56:32 by igsanche          #+#    #+#             */
/*   Updated: 2024/01/13 14:59:42 by igsanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_command
{
	int					pipe;
	int					redirect_output;
	int					redirect_input;
    struct s_command	*next;
} t_command;

typedef t_command *list;

typedef struct s_minishell
{
    char 				*PATH;
	list				commands;
} t_minishell;

//Commands
void    add_command_at_end(list *l, t_command *c);

#endif