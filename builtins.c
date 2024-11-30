#include "minishell.h"

int	is_builtin(char *str)
{
	if (strncmp(str, "cd", 3) == 0)
		return (1);
	if (strncmp(str, "exit", 5) == 0)
		return (1);
	return (0);
}

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

void	builtin_jobs(tcommand t, twaitpid *pid_stock)
{
	int	i;

	i = 0;
	refresh_pids_cache(pid_stock);
	while (i < pid_stock->background_commands)
	{
		show_line_as_jobs(i, pid_stock->inputs[i]);
		i++;
	}
}

void	builtin_fg(tcommand t, twaitpid *pid_stock)
{
	refresh_pids_cache(pid_stock);
	if (t.argc > 1)
	{
		exec_line_as_job(atoi(t.argv[1]) - 1, pid_stock);
	}
	else
	{
		exec_line_as_job(pid_stock->background_commands - 1, pid_stock);
	}
}
