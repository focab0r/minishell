


#include "minishell.h"


void add_pids(twaitpid *pid_stock, int *aux, tline *line)
{
    int     **new_pid_stock;
    tline   **new_lines;
    int     i;

    new_pid_stock = (int **) malloc ((pid_stock->background_commands + 1) * sizeof(int *));
    new_lines = (tline **) malloc ((pid_stock->background_commands + 1) * sizeof(tline *));
    i = 0;
    while (i < pid_stock->background_commands)
    {
        new_pid_stock[i] = pid_stock->waitpid_estructure[i];
        new_lines[i] = pid_stock->lines[i];
        i++;
    }
    new_pid_stock[i] = aux;
    new_lines[i] = line;
    pid_stock->background_commands++;
    free(pid_stock->waitpid_estructure);
    free(pid_stock->lines);
    pid_stock->waitpid_estructure = new_pid_stock;
    pid_stock->lines = new_lines;
}

int check_if_line_is_dead(tline *line, int *waitpid_list)
{
    int     i;
    int     status;
    pid_t   result;

    i = 0;
    while(i < line->ncommands)
    {
        result = waitpid(waitpid_list[i], &status, WNOHANG);
        if (result == 0)
            return (0);
        i++;
    }
    return (1);
}

void show_line_as_jobs(int num, tline *line)
{
    int i;
    int e;

    printf("[%d]+ Running\t\t", num);
    i = 0;
    while (i < line->ncommands)
    {
        if (i != 0)
            printf(" | ");
        printf("%s ", line->commands[i].filename);
        e = 0;
        while (e < line->commands[i].argc)
        {
            printf("%s ", line->commands[i].argv[e]);
            e++;
        }
        if (i == 0 && line->redirect_input)
            printf("< %s ", line->redirect_input);
        if (i == line->ncommands - 1 && line->redirect_output)
            printf("> %s ", line->redirect_output);
        if (i == 0 && line->redirect_error)
            printf("&> %s ", line->redirect_error);
        i++;
    }
    printf("\n");
    
}