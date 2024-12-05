#include "minishell.h"

int g_job = -1;
twaitpid *pid_stock;

void	sig_handler(int sig)
{
	int i;

	if (g_job != -1)
	{
		i = 0;
		while (i < pid_stock->ncommands[g_job])
		{
			if (pid_stock->waitpid_estructure[g_job][i] != 0)
				kill (pid_stock->waitpid_estructure[g_job][i], sig);
			i++;
		}
	}
	printf("\n");
}

void	init_vars()
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_handler = sig_handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
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
			refresh_pids_cache();
			line = tokenize(input);
			if (line == NULL)
				continue;
			aux = execute_commands(line);
			if (aux != NULL)
			{
				refresh_pids_cache();
				add_pids(aux, line->ncommands, input);
			}
			else
				free(input);
		}
	}
}
