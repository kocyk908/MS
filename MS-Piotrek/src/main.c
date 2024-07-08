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



int main(int ac, char **av, char **envp)
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
            execute_pipeline(cmd_list, gen, redirs, envp); //updated
            free_command(cmd_list);
        }
        free(input);
    }
    return (0);
}

/*
Update 07.07.24

Udało mi sie już jakoś połączyć procesy w pętlach. 
Póki co to działałem na harkodowanych zmiennych jak path, ilość komend itp
Na tą chwilę potrzeba:

1. Uzupełnić int num_of_cmds w s_gen - długość listy komend. Ja to mogę zrobić.
2. Uzupełnić char *path w s_command - ścieżka do programu np: "/usr/bin/cat"
3. Uzupełnić redirsy:
    a) int input_redir - będzie zawirać file descriptor będący wynikiem funckji open
    b) analogicznie output_redir;

Uzupełnienie tego powinno już pozwolić połączyć to wszystko.
Potem zajmiemy sie heredoc i append.

--------------------------------------------------------------------------

Robię tak że execute_pipeline przyjmie następujące informacje
1. input redirection w formie ścieżki pliku w postaci 
    stringa np: "infile.txt"
2. porzebuję ścieżki do każdej komendy znajdującej się command.
    Utworzyłem membere commant->path. Scieżka powinna wyglądać np:
    "/usr/bin/ls" dla programu ls 

*/