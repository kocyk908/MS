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

# include "../libft/libft.h"

typedef struct s_redirs
{
    int input_redir;     // <  Plik wejściowy
    char *input_redir1;   // <  ścieżka pliku wejściowego
    int is_heredoc;      // << Heredoc flag
    int output_redir;    // >  Plik wyjściowy
    char *output_redir1;    // >  ścieżka pliku wejściowego
    int is_append;       // >>  Append flag
} t_redirs;

typedef struct s_command
{
    char *path;
    char **args;
    t_redirs redirs;
    struct s_command *next;
} t_command;

typedef struct s_gen
{
    int num_of_cmds;
    int **pipes;
    int *pids;

} t_gen;

int is_builtin(char *cmd);
void execute_builtin(t_command *command);
int execute_pipeline(t_command *command, t_gen *gen, t_redirs *redirs, char **envp);
void execute_command(char *command);
void free_command(t_command *command);
t_command *parse_command(char *input);
char *find_path(char *cmd, char **envp);
size_t	ft_strcspn(const char *str, const char *delim);
char	*concat_path(const char *dir, const char *cmd);
size_t ft_strspn(const char *str, const char *delim);


#endif