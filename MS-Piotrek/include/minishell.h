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
# include <stdbool.h> 

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
void	execute_builtin(t_command *command, char **envp);
int execute_pipeline(t_command *command, t_gen *gen, t_redirs *redirs, char **envp);
void execute_command(char *command);
void free_command(t_command *command);
t_command *parse_command(char *input);
char	*find_path(char *cmd1, char **envp);
// char *find_path(char *cmd, char **envp);
size_t	ft_strcspn(const char *str, const char *delim);
char	*concat_path(const char *dir, const char *cmd);
size_t ft_strspn(const char *str, const char *delim);
void    print_error(char *cmd);
void	create_child_processes(t_command *command, t_gen *gen, char **envp);
void	close_pipes(t_gen *gen);
void	init_pipes(t_gen *gen);
//void	handle_input_redir(t_redirs *redirs);
void	ft_error(char *str);
void	ft_child_process(t_command *command, t_gen *gen, int i, char **envp);
void	process_input(t_gen *gen, t_redirs *redirs, char *input, char **envp);
void	init_structs(t_gen **gen, t_redirs **redirs);
t_command	*create_new_command(char *token);
void	handle_redirections(t_command *new_cmd, char *arg, char **saveptr2);
void	add_command_to_list(t_command **head, t_command **current, t_command *new_cmd);
void	parse_arguments(t_command *new_cmd, char *token);
char	*ft_strtok_r(char *str, const char *delim, char **saveptr);	// Dzieli delimiterem zdanie 

//redirections

void	handle_input_redir(t_redirs *redirs, char **saveptr2);
void	handle_heredoc(t_redirs *redirs, char **saveptr2);
void	handle_output_redir(t_redirs *redirs, char **saveptr2);
void	handle_append_redir(t_redirs *redirs, char **saveptr2);

#endif
