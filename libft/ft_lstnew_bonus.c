/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igsanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:56:32 by igsanche          #+#    #+#             */
/*   Updated: 2024/01/25 17:14:30 by igsanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*l;

	l = (t_list *) malloc (1 * sizeof(t_list));
	if (l == NULL)
	{
		return (NULL);
	}
	l->content = content;
	l->next = NULL;
	return (l);
}

/*
int main()
{
    t_list *l = ft_lstnew('c');
    printf("Valor: %c\n", l->content);
}
*/
