/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssousmat <ssousmat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:56:32 by igsanche          #+#    #+#             */
/*   Updated: 2025/03/15 19:10:29 by ssousmat         ###   ########.fr       */
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
char	*check_env(char *word, t_minishell *minishell, int *env_num)
{
	int		i;
	char	*header;

	i = 0;
	if (ft_strncmp(word, "?", 2) == 0)
		return ft_itoa(minishell->exit_value);
	while (minishell->env[i] != NULL)
	{
		header = get_env_header(minishell->env[i]);
		if (ft_strncmp(header, word, ft_strlen(header)+1) == 0)
		{
			if (env_num != NULL)
				*env_num = i;
			return (free(header), ft_strdup(ft_strchr(minishell->env[i], '=') + 1));
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

int	sustitute_word(char **word, char *start, char *end, t_minishell *minishell)
{
	char	*var;
	char	*str;
	int		len;
	int		i;

	len = end - start;
	str = (char *) malloc ((len + 2) * sizeof(char));
	ft_strlcpy(str, start, len + 2);
	var = check_env(str, minishell, NULL);
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

char	*replace_vars(char *word, t_minishell *minishell)
{
	int		i;
	char	*start;
	char	*end;
	int		is_not_in_d_quotes;

	i = 0;
	is_not_in_d_quotes = 1;
	while (word[i])
	{
		if (word[i] == '\'' && is_not_in_d_quotes)
			pass_till_comma(word, &i);
		if (word[i] == '$')
		{
			i++;
			start = &(word[i]);
			while (word[i] && ft_isalnum(word[i]))
				i++;
			end = &(word[i - 1]);
			if (start <= end)
				i = sustitute_word(&word, start, end, minishell);
			else if (word[i] == '?')
				i = sustitute_word(&word, start, end + 1, minishell);
		}
		if (word[i] == '"')
			is_not_in_d_quotes = (is_not_in_d_quotes+1) % 2;
		if (word[i])
			i++;
	}
	return (word);
}
