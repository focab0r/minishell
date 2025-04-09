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

#include "../minishell.h"

//Gestionar solo SIGINT
void	sig_handler(int sig)
{
	g_signal = sig;
	if (sig == 2)
	{
		ft_printf("\n");
		rl_on_new_line ();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == 3)
	{
		rl_redisplay();
	}
}
