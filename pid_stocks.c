


#include "minishell.h"


void add_pids(int *aux, int ncommands, char *input)
{
    int     **new_pid_stock;
    char    **new_input;
    int     *new_ncommands;
    int     i;

    new_pid_stock = (int **) malloc ((pid_stock->background_commands + 1) * sizeof(int *));
    new_input = (char **) malloc ((pid_stock->background_commands + 1) * sizeof(char *));
    new_ncommands = (int *) malloc ((pid_stock->background_commands + 1) * sizeof(int));
    if (new_pid_stock == NULL || new_input == NULL || new_ncommands == NULL)
    {
        perror("Memory allocation error");
        exit(1);
    }
    i = 0;
    while (i < pid_stock->background_commands)
    {
        new_pid_stock[i] = pid_stock->waitpid_estructure[i];
        new_input[i] = pid_stock->inputs[i];
        new_ncommands[i] = pid_stock->ncommands[i];
        i++;
    }
    new_pid_stock[i] = aux;
    new_input[i] = input;
    new_ncommands[i] = ncommands;
    pid_stock->background_commands++;
    if (pid_stock->waitpid_estructure != NULL)
    {
        free(pid_stock->waitpid_estructure);
        free(pid_stock->inputs);
        free(pid_stock->ncommands);
    }
    pid_stock->waitpid_estructure = new_pid_stock;
    pid_stock->inputs = new_input;
    pid_stock->ncommands = new_ncommands;
    i = 0;
    printf("[%d] %d\n", pid_stock->background_commands, aux[ncommands - 1]);
}

int check_if_line_is_dead(int ncommands, int *waitpid_list, int pid)
{
    int     i;
    int     status;
    pid_t   result;

    i = 0;
    while(i < ncommands)
    {
        if (waitpid_list[i] != 0)
        {
            if (pid != 0 && waitpid_list[i] == pid)
                return (2);
            result = waitpid(waitpid_list[i], &status, WNOHANG);
            if (result == 0)
                return (0);
        }
        i++;
    }
    return (1);
}

void show_line_as_jobs(int num, char *input, int is_dead)
{
    if (is_dead)
        printf("[%d]+ Done\t\t%s", num + 1, input);
    else
        printf("[%d]+ Running\t\t%s", num + 1, input);
}

void refresh_pids_cache(int pid)
{
    int i;
    int new_len;
    int     **new_pid_stock = NULL;
    char    **new_input = NULL;
    int     *new_ncommands = NULL;
    int dead;

    i = 0;
    new_len = pid_stock->background_commands;
    while (i < pid_stock->background_commands)
    {
        dead = check_if_line_is_dead(pid_stock->ncommands[i], pid_stock->waitpid_estructure[i], pid);
        if (dead)
        {
            if (dead == 1)
                show_line_as_jobs(i, pid_stock->inputs[i], 1);
            free(pid_stock->inputs[i]);
            pid_stock->ncommands[i] = 0;
            free(pid_stock->waitpid_estructure[i]);
            new_len--;
        }
        i++;
    }
    if (new_len > 0)
    {
        new_pid_stock = (int **) malloc ((pid_stock->background_commands) * sizeof(int *));
        new_input = (char **) malloc ((pid_stock->background_commands) * sizeof(char *));
        new_ncommands = (int *) malloc ((pid_stock->background_commands) * sizeof(int));
        if (new_pid_stock == NULL || new_input == NULL || new_ncommands == NULL)
        {
            perror("Memory allocation error");
            exit(1);
        }
    }
    i = 0;
    new_len = 0;
    while (i < pid_stock->background_commands)
    {
        if (pid_stock->ncommands[i] != 0)
        {
            new_pid_stock[new_len] = pid_stock->waitpid_estructure[i];
            new_input[new_len] = pid_stock->inputs[i];
            new_ncommands[new_len] = pid_stock->ncommands[i];
            new_len++;
        }
        i++;
    }
    free(pid_stock->waitpid_estructure);
    free(pid_stock->inputs);
    free(pid_stock->ncommands);
    pid_stock->waitpid_estructure = new_pid_stock;
    pid_stock->inputs = new_input;
    pid_stock->ncommands = new_ncommands;
    pid_stock->background_commands = new_len;
}

void exec_line_as_job(int nline)
{
    int i;
    int status;
    if (nline >= 0 && nline < pid_stock->background_commands)
    {
        i = 0;
        while (i < pid_stock->ncommands[nline])
        {
            waitpid(pid_stock->waitpid_estructure[nline][i], &status, 0);
            i++;
        }
        if (0 < pid_stock->ncommands[nline])
            refresh_pids_cache(pid_stock->waitpid_estructure[nline][0]);

    }
    else
        printf("fg: %d: job does not exist\n", nline + 1);
}
