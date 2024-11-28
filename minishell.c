


#include "minishell.h"

void print_line(tline *line)
{
	printf("--------------------------------\n");
	printf("Nº commands: %d\n", line->ncommands);
	int i = 0;
	int e;
	while (i < line->ncommands)
	{
		tcommand c = (line->commands)[i];
		printf("<<<<< %d >>>>>\n", i);
		printf("--> Command name: %s\n", c.filename);
		printf("--> Nº Argc: %d\n", c.argc);
		e = 0;
		while (e < c.argc)
		{
			printf("----> Arg: %s\n", (c.argv)[e]);
			e++;
		}
		i++;
	}
	if (line->redirect_input != NULL)
		printf("Input redirected to: %s\n", line->redirect_input);
	if (line->redirect_output != NULL)
		printf("Output redirected to: %s\n", line->redirect_output);
	if (line->redirect_error != NULL)
		printf("Error redirected to: %s\n", line->redirect_error);
	if (line->background == 1)
		printf("The last command will be redirected to bg\n");
	printf("--------------------------------\n");
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
	len += strlen(user);
	len += strlen(max_path);
	len += 11;
    len += sizeof(GREEN) + sizeof(RESET) + sizeof(BLUE) + sizeof(RED) + sizeof(MAGENTA);
	str = (char *) malloc (len*sizeof(char));
    strlcpy(str, GREEN, strlen(GREEN) + 1);
	strlcpy(str + strlen(str), user, strlen(user) + 1);
    strlcpy(str + strlen(str), BLUE, strlen(BLUE) + 1);
	strlcpy(str + strlen(str), " [at] ", 7);
    strlcpy(str + strlen(str), MAGENTA, strlen(MAGENTA) + 1);
	strlcpy(str + strlen(str), max_path, strlen(max_path) + 1);
    strlcpy(str + strlen(str), RED, strlen(RED) + 1);
	strlcpy(str + strlen(str), " $> ", 5);
    strlcpy(str + strlen(str), RESET, strlen(RESET) + 1);
	return(str);
}

int main(int argc, char **argv, char **env)
{
    //ft_pipe(argc, argv, env);
    char        		*input;
    tline      			*line;
    struct sigaction	sa;
    char                *cursor;
	int					*aux;
	twaitpid			*pid_stock;


	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sig_handler;
	sigaction(SIGINT, &sa, NULL); //Control-C
    line = (tline *) malloc (sizeof(tline));
	pid_stock = (twaitpid *) malloc (sizeof(twaitpid));
	pid_stock->background_commands = 0;
    while(1)
    {
        cursor = get_cursor();
        //input = readline(cursor);
		printf("%s ", cursor);
		fflush(stdout);
		input = get_next_line(STDIN_FILENO);
		if (input)
        {
            //add_history(input);
            line = tokenize(input);
            //replace_vars(m, line);
            aux = execute_commands(line, pid_stock);
			if (aux != NULL)
			{
				add_pids(pid_stock, aux, line);
			}
            //print_line(line);
        }
        else //Control-D
            exit(0);
		free(cursor);
    }
}