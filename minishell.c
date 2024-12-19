#include "minishell.h"

twaitpid *pid_stock;
int waiting = 0;

void	sig_handler()
{
	if (!waiting)
		printf("\nmsh> ");
	else
		printf("\n");
	fflush(stdout);
}

void	init_vars()
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	pid_stock = (twaitpid *) malloc (sizeof(twaitpid));
	if (!(pid_stock))
	{
		perror("Memory allocation error");
		exit(1);
	}
	pid_stock->background_commands = 0;

}

int	main()
{
	char				*input;
	tline				*line;
	int					*aux;

	init_vars();
	while (1)
	{
		printf("msh> ");
		fflush(stdout);
		input = get_next_line(STDIN_FILENO);
		if (input)
		{
			refresh_pids_cache(0);
			line = tokenize(input);
			if (line == NULL)
				continue;
			waiting = 1;
			aux = execute_commands(line);
			if (aux != NULL)
			{
				refresh_pids_cache(0);
				add_pids(aux, line->ncommands, input);
			}
			else
				free(input);
			waiting = 0;

		}
	}
}
