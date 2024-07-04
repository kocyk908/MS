#include "minishell.h"

void execute_pipeline(t_command *command, t_gen *gen) {

    gen->num_of_cmds = 2;
    int i;
    int id;

    i = 0;

    gen->pipes = malloc(gen->num_of_cmds * sizeof(int *)); // to free
    while(i < gen->num_of_cmds)
    {
        gen->pipes[i] = malloc(2 * sizeof(int)); // to free
        if(pipe(gen->pipes[i]) < 0)
            // ft_error("Unable to create pipe"); // function to create
        i++;
    }
    i = 0;
    gen->pids = malloc(gen->num_of_cmds * sizeof(int)); // to free
    while(i < gen->num_of_cmds)
    {
         gen->pids[i] = fork();
         if(gen->pids[i] == 0)
         {
            ft_child_process(...); //finished here
         }
         i++;
    }
    i = 0;


    // id = fork();
    // if(id == 0)
    // {
    //     ft_child_process();
    // } 


    // while(command)
    // {
    //     i++;

    //     printf("actual command: %s\n", command->args[0]);
    //     command = command->next;
    // } 
}
/*
void execute_pipeline(t_command *command, t_gen *gen) {
    int pipefd[2];
    int fd_in = 0; // Plik deskryptor dla wejścia (stdin)
    pid_t pid;

    while (command) {
        if (command->next && pipe(pipefd) == -1) {
            perror("pipe failed");
            exit(EXIT_FAILURE);
        }

        if (!is_builtin(command->args[0])) {
            pid = fork();

            if (pid < 0) {
                perror("fork failed");
                exit(EXIT_FAILURE);
            } else if (pid == 0) {
                if (command->redirs.input_redir != -1) {
                    dup2(command->redirs.input_redir, 0);
                    close(command->redirs.input_redir);
                } else {
                    dup2(fd_in, 0);
                }
                if (command->redirs.output_redir != -1) {
                    dup2(command->redirs.output_redir, 1);
                    close(command->redirs.output_redir);
                } else if (command->next) {
                    dup2(pipefd[1], 1);
                    close(pipefd[0]);
                }
                execvp(command->args[0], command->args);
                perror("execvp failed");
                exit(EXIT_FAILURE);
            } else {
                wait(NULL);
                close(pipefd[1]);
                fd_in = pipefd[0]; // Przekierowanie dla następnego polecenia
            }
        } else {
            execute_builtin(command);
            if (strcmp(command->args[0], "exit") == 0) {
                free_command(command);
                exit(0);
            }
        }
        command = command->next;
    }
}*/