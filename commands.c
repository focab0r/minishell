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

list	*get_final_node(list l)
{
	list	aux;
	list	pre_aux;

	if (l == NULL)
		return (NULL);
	aux = l;
	while(aux)
	{
		pre_aux = aux;
		aux = aux->next;
	}
	return(pre_aux);
}

void    add_command_at_end(list *l, t_command *c)
{
    list		aux;

	c->next = NULL;
	aux = get_final_node(l);
	if (aux)
	{
		aux->next = c;
	}
	else
	{
		*l = c;
	}
}