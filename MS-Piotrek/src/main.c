#include "minishell.h"

void free_command(t_command *command) {
    t_command *temp;
    while (command) {
        temp = command;
        command = command->next;
        free(temp->args);
        free(temp);
    }
}

int is_builtin(char *cmd) {
    return (strcmp(cmd, "echo") == 0 || strcmp(cmd, "cd") == 0 ||
            strcmp(cmd, "pwd") == 0 || strcmp(cmd, "exit") == 0);
}



int main(int ac, char **av)
{
    (void)ac;
    (void)av;
    char *input;
    t_gen *gen;
    t_redirs *redirs;


    gen = malloc(sizeof(t_gen));
    redirs = malloc(sizeof(t_redirs));
    redirs->input_redir1 = NULL;
    while (1)
    {
        input = readline("msh> ");
        if (input)
        {
            add_history(input);
            t_command *cmd_list = parse_command(input);
            execute_pipeline(cmd_list, gen, redirs); //updated
            free_command(cmd_list);
        }
        free(input);
    }
    return (0);
}
