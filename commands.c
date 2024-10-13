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

void add_argument_at_end(c_list *l, char *argv)
{
	int		len;
	int		i;
	char	**new_argv;

	if ((*l)->argv == NULL)
	{
		(*l)->argv = (char **) malloc (2 * sizeof(char *));
		((*l)->argv)[0] = argv;
		((*l)->argv)[1] = NULL;
		return ;
	}
	len = 0;
	while (((*l)->argv)[len] != NULL)
		len++;
	new_argv = (char **) malloc ((len+1) * sizeof(char *));
	i = 0;
	while (((*l)->argv)[i] != NULL)
	{
		new_argv[i] = ((*l)->argv)[i];
		i++;
	}
	new_argv[i] = argv;
	free((*l)->argv);
	(*l)->argv = new_argv;
}

void init_command(c_list *l)
{
	(*l)->argv = NULL;
	(*l)->argc = 0;
	(*l)->filename = NULL;
}