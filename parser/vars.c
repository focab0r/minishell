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

char	*get_env_header(char *env_var)
{
	int		len;
	char	*header;

	len = ft_strchr(env_var, '=') - env_var + 1;
	header = (char *) malloc (len * sizeof(char));
	ft_strlcpy(header, env_var, len);
	return (header);
}

// Gets a header, the env vars, and a pointer to a int
// Returns the value of the var pointed by header, NULL if no var is founded
// If env_num is not NULL, set the pointer to the pos of the var in env 
char	*check_env(char *word, char **env, int *env_num)
{
	int		i;
	char	*header;

	i = 0;
	while (env[i] != NULL)
	{
		header = get_env_header(env[i]);
		if (ft_strncmp(header, word, ft_strlen(header)) == 0)
		{
			if (env_num != NULL)
				*env_num = i;
			return (free(header), ft_strdup(ft_strchr(env[i], '=') + 1));
		}
		free(header);
		i++;
	}
	return (NULL);
}

char	*concat_word(char *command, char *start, char *end, char *var)
{
	int		len;
	char	*str;
	int		i;

	len = start - command - 1;
	len += ft_strlen(var);
	end++;
	len += ft_strlen(end);
	str = (char *) malloc ((len + 1) * sizeof(char));
	i = 0;
	while (command != start)
		str[i++] = *(command++);
	i--;
	while (*var)
		str[i++] = *(var++);
	while (*end)
		str[i++] = *(end++);
	str[i] = '\0';
	return (str);
}

int	sustitute_word(char **word, char *start, char *end, char **env)
{
	char	*var;
	char	*str;
	int		len;
	int		i;

	len = end - start;
	str = (char *) malloc ((len + 2) * sizeof(char));
	ft_strlcpy(str, start, len + 2);
	var = check_env(str, env, NULL);
	if (var == NULL)
	{
		var = (char *) malloc (1 * sizeof(char));
		var[0] = '\0';
	}
	free(str);
	str = concat_word(*word, start, end, var);
	i = (start - *word - 1) + ft_strlen(var);
	free(var);
	free(*word);
	*word = str;
	return (i);
}

char	*replace_vars(char *word, char **env)
{
	int		i;
	char	*start;
	char	*end;

	i = 0;
	while (word[i])
	{
		if (word[i] == '\'')
			pass_till_comma(word, &i);
		if (word[i] == '$')
		{
			i++;
			start = &(word[i]);
			while (word[i] && ft_isalnum(word[i]))
				i++;
			end = &(word[i - 1]);
			if (start <= end)
				i = sustitute_word(&word, start, end, env);
			else if (word[i] == '?')
				i = sustitute_word(&word, start, end + 1, env);
		}
		if (word[i])
			i++;
	}
	return (word);
}
