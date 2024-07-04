#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>




typedef struct s_redirs
{
    int input_redir;     // <  Plik wejściowy
    int is_heredoc;      // << Heredoc flag
    int output_redir;    // >  Plik wyjściowy
    int is_append;       // >>  Append flag
} t_redirs;

typedef struct s_command
{
    char **args;
    t_redirs redirs;
    struct s_command *next;
} t_command;

typedef struct s_gen
{
    int num_of_cmds;
    int **pipes;
    int **pids;

} t_gen;

int is_builtin(char *cmd);
void execute_builtin(t_command *command);
void execute_pipeline(t_command *command, t_gen *gen);
void execute_command(char *command);
void free_command(t_command *command);
t_command *parse_command(char *input);



#endif
