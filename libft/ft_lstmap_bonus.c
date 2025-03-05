/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igsanche <igsanche@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 12:39:58 by igsanche          #+#    #+#             */
/*   Updated: 2024/01/25 21:06:49 by igsanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_all_nodes(t_list *new_list, void (*del)(void *))
{
	t_list	*aux;
	t_list	*post;
	int		size;

	aux = new_list;
	size = ft_lstsize(new_list);
	while (size > 0)
	{
		post = aux->next;
		ft_lstdelone(aux, del);
		aux = post;
		size--;
	}
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*aux;
	void	*c;

	if (lst == NULL || f == NULL || del == NULL)
	{
		return (NULL);
	}
	new_list = NULL;
	while (lst != NULL)
	{
		c = f(lst->content);
		aux = ft_lstnew(c);
		if (aux == NULL)
		{
			del(c);
			free_all_nodes(new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, aux);
		lst = lst->next;
	}
	return (new_list);
}
