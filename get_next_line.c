/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igsanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:56:32 by igsanche          #+#    #+#             */
/*   Updated: 2024/01/13 14:59:42 by igsanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Main function of GNL
//It first check if there is something in str_saved. 
//If there is a "\n" --> Then returns str
//If not --> Prepare str2, the prepare str
//If we nedd to read, we call prepare_str
//To concat str2 + str, we call return_str
char	*get_next_line(int fd)
{
	char		*str;
	char		*str2;
	static char	*str_saved = NULL;
	int			len;

	str = NULL;
	str2 = NULL;
	len = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (clean(&str_saved, 0, 0, 2));
	if (str_saved != NULL)
	{
		while (str_saved[len] != '\n' && str_saved[len] != '\0')
			len++;
		if (str_saved[len] == '\n')
			return (str_saved_contains_n(&str, &len, &str_saved));
		else
		{
			str2 = prepare_str(0, &str_saved, 0, 1);
		}
	}
	len = 0;
	str = prepare_str(fd, &str_saved, &len, 0);
	return (return_str(len, &str2, &str, &str_saved));
}

//If op = 0 --> Prepare str
//If op = 1 --> Prepare str2
//cr_f[0] --> fd
//cr_f[1] --> char_reads
char	*prepare_str(int fd, char **str_saved, int *error, int op)
{
	char	*str;
	int		cr_f[2];
	int		len;

	if (op == 0)
	{
		cr_f[0] = fd;
		str = (char *) malloc ((BUFFER_SIZE + 1) * sizeof(char));
		if (str == NULL)
			return (*error = 1, NULL);
		cr_f[1] = read (fd, str, BUFFER_SIZE);
		if (cr_f[1] < 0)
			return (clean(&str, error, 1, 0));
		if (cr_f[1] == 0)
			return (clean(&str, error, 0, 0));
		str[cr_f[1]] = '\0';
		return (read_while(cr_f, error, &str, str_saved));
	}
	len = strlcpy_and_strlen(*str_saved, NULL, 0, 0);
	str = (char *) malloc ((len + 1) * sizeof(char));
	if (str == NULL)
		return (clean(str_saved, 0, 0, 1));
	strlcpy_and_strlen(str, *str_saved, len, 1);
	str[len] = '\0';
	return (free (*str_saved), *str_saved = NULL, str);
}

//This is the loop that reads till it finds a "\n" or a "\0"
//When it finds one of them, it calls read_founded
//Else, it calls read_continue
char	*read_while(int *cr_f, int *error, char **str, char **str_saved)
{
	int		ie[2];
	int		offset;
	char	*result;

	offset = 0;
	while (1)
	{
		ie[0] = 0;
		ie[1] = 1;
		while (ie[0] < cr_f[1] && ie[1])
		{
			if ((*str)[ie[0] + offset] == '\n')
				ie[1] = 0;
			else
				ie[0]++;
		}
		if ((*str)[ie[0] + offset] == '\n')
			return (read_founded(error, str, str_saved, ie[0] + offset));
		else
		{
			result = read_continue(cr_f, &offset, str, error);
			if (*error != 0)
				return (result);
		}
	}
}

//Called by main GNL when str_saved contains a "\n"
char	*str_saved_contains_n(char **str, int *i, char **str_saved)
{
	char	*str2;
	int		len;

	*str = (char *) malloc ((*i + 2) * sizeof(char));
	if (*str == NULL)
		return (clean(str_saved, 0, 0, 1));
	strlcpy_and_strlen(*str, *str_saved, *i, 1);
	(*str)[*i] = '\n';
	(*str)[*i + 1] = '\0';
	len = strlcpy_and_strlen(&((*str_saved)[*i + 1]), NULL, 0, 0);
	if (len == 0)
		clean(str_saved, 0, 0, 3);
	else
	{
		str2 = (char *) malloc ((len + 1) * sizeof(char));
		if (!str2)
			return (free (*str), clean(str_saved, 0, 0, 1));
		strlcpy_and_strlen(str2, &((*str_saved)[*i + 1]), len, 1);
		str2[len] = '\0';
		free(*str_saved);
		*str_saved = str2;
	}
	return (*str);
}

//Concat str2 + str, and the returns it
char	*return_str(int error, char **str2, char **str, char **str_saved)
{
	int	len_str;
	int	len_str2;

	if (error == 1)
	{
		if (*str2 != NULL)
			free (*str2);
		return (clean(str_saved, 0, 0, 1));
	}
	if (*str == NULL)
		return (*str2);
	if (*str2 != NULL)
	{
		len_str = strlcpy_and_strlen(*str, NULL, 0, 0);
		len_str2 = strlcpy_and_strlen(*str2, NULL, 0, 0);
		*str2 = ft_realloc(*str2, len_str + 1);
		if (*str2 == NULL)
			return (free (*str), clean(str_saved, 0, 0, 1));
		strlcpy_and_strlen(&((*str2)[len_str2]), *str, len_str, 1);
		(*str2)[len_str2 + len_str] = '\0';
		return (free (*str), *str2);
	}
	return (*str);
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
	int fd = open("file.txt", O_CREAT | O_RDONLY);
	char *string = get_next_line(fd);
	while (string != NULL)
	{
		printf("%s-->(end)<--\n", string);
		string = get_next_line(fd);
	}
}
*/