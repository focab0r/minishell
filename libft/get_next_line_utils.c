/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igsanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:56:32 by igsanche          #+#    #+#             */
/*   Updated: 2024/01/13 14:59:42 by igsanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc(char *str, int amount)
{
	int		len;
	char	*str2;

	len = strlcpy_and_strlen(str, NULL, 0, 0);
	str2 = (char *) malloc (len + amount);
	if (str2 == NULL)
	{
		free(str);
		free(str2);
		return (NULL);
	}
	strlcpy_and_strlen(str2, str, len, 1);
	free(str);
	return (str2);
}

// op = 1 --> strlcpy
// op = 0 --> strlen
size_t	strlcpy_and_strlen(char *dest, const char *src, size_t n, int op)
{
	unsigned int	i;

	if (op == 1)
	{
		i = 0;
		while (i < n)
		{
			dest[i] = src[i];
			i++;
		}
	}
	else
	{
		i = 0;
		while (dest[i] != '\0')
		{
			i++;
		}
	}
	return (i);
}

//op = 0 --> Clean in prepare_str
//op = 1 --> Clean str_saved
//op = 2 --> Clean if the fd is invalid
//op = 3 --> Clean in str_saved_contains_n
char	*clean(char **str, int *error, int malloc_value, int op)
{
	if (op == 0)
	{
		*error = malloc_value;
		free(*str);
	}
	else if (op == 1)
	{
		if (*str != NULL)
		{
			free(*str);
			*str = NULL;
		}
	}
	else if (op == 2)
	{
		if (*str != NULL)
			free(*str);
		*str = NULL;
	}
	else if (op == 3)
	{
		free(*str);
		*str = NULL;
	}
	return (NULL);
}

//Called when read_while founds a "\n" or "\0". 
//It prepare str_sved, and return str2
char	*read_founded(int *error, char **str, char **str_saved, int i_offset)
{
	int		len_str;
	int		len_str_saved;
	char	*str2;

	len_str_saved = strlcpy_and_strlen(&((*str)[i_offset + 1]), NULL, 0, 0);
	if (len_str_saved == 0)
		*str_saved = NULL;
	else
	{
		*str_saved = (char *) malloc ((len_str_saved + 1) * sizeof(char));
		if (*str_saved == NULL)
			return (clean(str, error, 1, 0));
		strlcpy_and_strlen(*str_saved,
			&((*str)[i_offset + 1]), len_str_saved, 1);
		(*str_saved)[len_str_saved] = '\0';
	}
	(*str)[i_offset + 1] = '\0';
	len_str = strlcpy_and_strlen(*str, NULL, 0, 0);
	str2 = (char *) malloc ((len_str + 1) * sizeof(char));
	if (str2 == NULL)
		return (clean(str, error, 1, 0));
	strlcpy_and_strlen(str2, *str, len_str, 1);
	(str2)[len_str] = '\0';
	free (*str);
	return (str2);
}

//Called when read_while wants to read a new buffered-line
char	*read_continue(int *cr_f, int *offset, char **str, int *error)
{
	int		len_str;
	char	*str2;

	len_str = strlcpy_and_strlen(*str, NULL, 0, 0);
	*offset = len_str;
	str2 = (char *) malloc ((BUFFER_SIZE + 1) * sizeof(char));
	if (str2 == NULL)
		return (clean(str, error, 1, 0));
	cr_f[1] = read (cr_f[0], str2, BUFFER_SIZE);
	*str = ft_realloc(*str, cr_f[1] + 1);
	if (*str == NULL)
		return (clean(&str2, error, 1, 0));
	strlcpy_and_strlen(&((*str)[len_str]), str2, cr_f[1], 1);
	(*str)[len_str + (cr_f[1])] = '\0';
	free (str2);
	if (cr_f[1] == 0)
		return (*error = 2, *str);
	return (NULL);
}
