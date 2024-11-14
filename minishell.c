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

#include "minishell.h"

void    save_env(t_minishell *m)
{
    m->PATH = getenv("PATH");
}

char   *get_cursor()
{
    char    *user;
    char	max_path[PATH_MAX];
    int		len;
	char	*str;

	user = getenv("USER");
    getcwd(max_path, sizeof(max_path));
	len = 0;
	len += ft_strlen(user);
	len += ft_strlen(max_path);
	len += 11;
	str = (char *) malloc (len*sizeof(char));
	ft_strlcpy(str, user, ft_strlen(user) + 1);
	ft_strlcpy(str + ft_strlen(str), " [at] ", 7);
	ft_strlcpy(str + ft_strlen(str), max_path, ft_strlen(max_path) + 1);
	ft_strlcpy(str + ft_strlen(str), " $> ", 5);
	return(str);
}

int main(int argc, char **argv, char **env)
{
    //ft_pipe(argc, argv, env);
    t_minishell m;
    char        *input;
    t_line      *line;
    struct sigaction	sa;
    char                *cursor;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sig_handler;
	sigaction(SIGINT, &sa, NULL); //Control-C
    save_env(&m);
    line = (t_line *) malloc (sizeof(t_line));
    while(1)
    {
        cursor = get_cursor();
        input = readline(cursor);
        if (input)
        {
            add_history(input);
            parse_input(line, input);
            replace_vars(m, line);
            escape_quotes(line);
            expand_alias(m, line);
            execute_commands(line, env);
            //print_line(line);
        }
        else //Control-D
            exit(0);
		free(cursor);
    }
}