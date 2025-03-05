/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igsanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:56:32 by igsanche          #+#    #+#             */
/*   Updated: 2024/01/25 18:06:08 by igsanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_char_on_func(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

void	see_first(char const *s1, char const *set, int *n1)
{
	int	flag;

	flag = 1;
	while (s1[*n1] != '\0' && flag == 1)
	{
		if (is_char_on_func(s1[*n1], set))
		{
			(*n1)++;
		}
		else
		{
			flag = 0;
		}
	}
}

void	see_second(char const *s1, char const *set, int *n2)
{
	int	flag;

	flag = 1;
	while (*n2 >= 0 && flag == 1)
	{
		if (is_char_on_func(s1[*n2], set))
		{
			(*n2)--;
		}
		else
		{
			flag = 0;
		}
	}
}

char	*ret_func(char *str2, char const *s1, int *n12, int flag)
{
	if (flag == 1)
	{
		if (str2 == NULL)
			return (NULL);
		ft_strlcpy(str2, &(s1[n12[0]]), n12[1] - n12[0] + 2);
		return (str2);
	}
	else if (flag == 2)
	{
		if (str2 == NULL)
			return (NULL);
		str2[0] = s1[n12[1]];
		str2[1] = '\0';
		return (str2);
	}
	else
	{
		if (str2 == NULL)
			return (NULL);
		str2[0] = 0;
		return (str2);
	}
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		n12[12];
	char	*str2;

	n12[0] = 0;
	n12[1] = 0;
	see_first(s1, set, &(n12[0]));
	n12[1] = ft_strlen(s1)-1;
	see_second(s1, set, &(n12[1]));
	if (n12[1] > n12[0])
	{
		str2 = (char *) malloc ((n12[1] - n12[0] + 2) * sizeof(char));
		return (ret_func(str2, s1, n12, 1));
	}
	else if (n12[1] == n12[0])
	{
		str2 = (char *) malloc (2 * sizeof(char));
		return (ret_func(str2, s1, n12, 2));
	}
	else
	{
		str2 = (char *) malloc (sizeof(char));
		return (ret_func(str2, s1, n12, 3));
	}
	return (str2);
}
/*
int main()
{
	char *str = "abcdba";
	printf("%s", ft_strtrim(str, "acb")); 
}
*/
