/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssousmat <ssousmat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:12:55 by ssousmat          #+#    #+#             */
/*   Updated: 2025/04/02 22:23:08 by ssousmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	builtin_exit(t_minishell *mini, t_command cmd)
{
	if (mini->line->ncommands == 1)
		ft_printf_2("exit\n");
	if (cmd.argc > 1)
	{
		if (!ft_isnum(cmd.argv[1]))
		{
			ft_printf_2("minishell: exit: %s: numeric argument required\n", \
						cmd.argv[1]);
			exit(2);
		}
		else if (cmd.argc > 2)
		{
			ft_printf_2("minishell: exit: too many arguments\n");
			if (mini->line->ncommands == 1)
				return (1);
			exit(1);
		}
		exit(ft_atoi((const char*)cmd.argv[1]));
	}
	else
		exit(0);
}
