#include "minishell.h"


void	builtin_cd(tcommand t)
{
	if (t.argc > 1)
	{
		if (chdir(t.argv[1]))
			printf("Invalid path!\n");
	}
	else
	{
		if (chdir(getenv("HOME")))
			printf("Invalid path!\n");
	}
}

void	builtin_jobs()
{
	int	i;

	i = 0;
	refresh_pids_cache(0);
	while (i < pid_stock->background_commands)
	{
		show_line_as_jobs(i, pid_stock->inputs[i], 0);
		i++;
	}
}

void	builtin_fg(tcommand t)
{
	refresh_pids_cache(0);
	if (t.argc > 1)
	{
		exec_line_as_job(atoi(t.argv[1]) - 1);
	}
	else
	{
		exec_line_as_job(pid_stock->background_commands - 1);
	}
}
