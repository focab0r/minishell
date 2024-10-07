/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igsanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:56:32 by igsanche          #+#    #+#             */
/*   Updated: 2024/01/25 20:13:21 by igsanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_num_ch(char const *s, char c)
{
	int	i;
	int	count;
	int	flag;

	flag = 0;
	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != '\0' && s[i + 1] != c && flag == 1)
		{
			count++;
		}
		if (s[i] != c)
		{
			flag = 1;
		}
		i++;
	}
	return (count + flag);
}

int	count_char(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		i++;
	}
	return (i);
}

void	ineficient(char **origin, char c, int *ie)
{
	while (**origin == c)
		(*origin)++;
	ie[1] = count_char(*origin, c);
}

void	free_all(char **str, int count, int failed_malloc)
{
	int	i;

	i = 0;
	while (i < failed_malloc)
	{
		free(str[i]);
		i++;
	}
	free(str[count]);
	free(str);
}

char	**ft_split(char const *s, char c)
{
	int		count;
	char	**str;
	char	*str2;
	char	*origin;
	int		ie[2];

	ie[0] = 0;
	count = count_num_ch(s, c);
	str = (char **) malloc ((count + 1) * sizeof(char *));
	if (str == NULL)
		return (free (str), NULL);
	str[count] = NULL;
	origin = (char *)s;
	while (ie[0] < count)
	{
		ineficient(&origin, c, ie);
		str2 = (char *) malloc ((ie[1] + 1) * sizeof(char));
		if (str2 == NULL)
			return (free(str2), free_all(str, count, ie[0]), NULL);
		ft_strlcpy(str2, origin, ie[1] + 1);
		origin = ft_strchr(origin, c);
		str[ie[0]] = str2;
		(ie[0])++;
	}
	return (str);
}

/*
int main()
{
	char **str;
	str = ft_split("hello!", ' ');
	int i = 0;
	while (str[i] != NULL)
	{
		printf("%s\n", str[i]);
		i++;
	}
	printf("%s\n", str[i]);
	free_all(str);
	atexit(runleaks);
}
*/