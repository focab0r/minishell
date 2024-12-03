#include "minishell.h"

void	sig_handler()
{
	printf("\n");
}

void	init_vars(twaitpid **pid_stock)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sig_handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	*pid_stock = (twaitpid *) malloc (sizeof(twaitpid));
	if (!(*pid_stock))
	{
		perror("Memory allocation error");
		exit(1);
	}
	(*pid_stock)->background_commands = 0;

}

int	main()
{
	char				*input;
	tline				*line;
	int					*aux;
	twaitpid			*pid_stock;

	init_vars(&pid_stock);
	while (1)
	{
		printf("msh> ");
		fflush(stdout);
		input = get_next_line(STDIN_FILENO);
		if (input)
		{
			refresh_pids_cache(pid_stock);
			line = tokenize(input);
			if (line == NULL)
				continue;
			aux = execute_commands(line, pid_stock);
			if (aux != NULL)
			{
				refresh_pids_cache(pid_stock);
				add_pids(pid_stock, aux, line->ncommands, input);
			}
			else
				free(input);
		}
	}
}
