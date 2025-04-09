/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssousmat <ssousmat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:56:32 by igsanche          #+#    #+#             */
/*   Updated: 2025/04/09 14:06:30 by ssousmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	change_var(t_minishell *minishell, int *i, char **word)
{
	char	*start;
	char	*end;

	(*i)++;
	start = &((*word)[*i]);
	while ((*word)[*i] && ft_isalnum((*word)[*i]))
		(*i)++;
	end = &((*word)[*i - 1]);
	if (start <= end)
		*i = sustitute_word(word, start, end, minishell);
	else if ((*word)[*i] == '?')
		*i = sustitute_word(word, start, end + 1, minishell);
}

char	*replace_vars(char *word, t_minishell *minishell)
{
	int		i;
	int		is_not_in_d_quotes;

	i = 0;
	is_not_in_d_quotes = 1;
	while (word[i])
	{
		if (word[i] == '\'' && is_not_in_d_quotes)
			pass_till_comma(word, &i);
		if (word[i] == '$')
		{
			change_var(minishell, &i, &word);
		}
		if (word[i] == '"')
			is_not_in_d_quotes = (is_not_in_d_quotes + 1) % 2;
		if (word[i])
			i++;
	}
	return (word);
}
