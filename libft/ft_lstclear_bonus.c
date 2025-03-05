/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igsanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:56:32 by igsanche          #+#    #+#             */
/*   Updated: 2024/01/13 14:59:42 by igsanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*lista;
	t_list	*anterior;

	anterior = *lst;
	if (anterior != NULL)
	{
		lista = anterior->next;
		while (lista != NULL)
		{
			del(anterior->content);
			free(anterior);
			anterior = lista;
			lista = lista->next;
		}
		del(anterior->content);
		free(anterior);
	}
	*lst = NULL;
}
