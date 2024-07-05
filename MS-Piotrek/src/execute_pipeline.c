#include "minishell.h"

void ft_error(char *str)
{
    printf("%s\n", str); // place perror
}

void ft_child_process(t_command *command, t_gen *gen, t_redirs *redirs, int i)
{
    int input;

    input = 0;
    if(i == 0)
    {
        
        if(redirs->input_redir)
        {
            input = open(redirs->input_redir, O_RDONLY);
            if(input == -1)
                ft_error("Unable to open a file");
        } 
        if(dup2(input, 0))
            ft_error("Unable to change fd");
        if(dup2(gen->pipes[i][1], 1));
            ft_error("Unable to change fd");
        // execve(command->args[0], ) // need path

    }


}

int execute_pipeline(t_command *command, t_gen *gen, t_redirs *redirs) {

    gen->num_of_cmds = 3;
    int i;
    int id;

    i = 0;
    gen->pipes = malloc((gen->num_of_cmds - 1) * sizeof(int *)); // to free
    while(i < gen->num_of_cmds - 1)
    {
        gen->pipes[i] = malloc(2 * sizeof(int)); // to free
        if(pipe(gen->pipes[i]) == -1)
            ft_error("Unable to create pipe"); 
        i++;
    }
    i = 0;
    gen->pids = malloc((gen->num_of_cmds + 1) * sizeof(int)); // to free

    i = 0;
    while(command)
    {
        printf("path to cmd: %s\n", command->path);
         gen->pids[i] = fork();
         if(gen->pids[i] == 0)
         {
            // ft_child_process(command, gen, redirs, i); //finished here
            return 0;
         }
         command = command->next;
         i++;
    }
    i = 0;
    while(i < gen->num_of_cmds)
    {
        wait(NULL); 
        i++;
    }
    return 0;
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