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
    int is_heredoc;      // << Heredoc flag
    int output_redir;    // >  Plik wyjściowy
    int is_append;       // >>  Append flag
} t_redirs;

typedef struct s_command
{
    char *path;
    char **args;
    t_redirs redirs;
    struct s_command *next;
} t_command;

typedef struct s_history
{
    int num;
    char *input;
    struct s_history *next;
}   t_history;

typedef struct s_gen
{
    int num_of_cmds;
    int **pipes;
    int *pids;
    char **envs;
    t_history *history;
} t_gen;

int is_builtin(char *cmd);
void	execute_builtin(t_command *command, t_gen *gen);
void execute_command(char *command);
// char *find_path(char *cmd, char **envp);
char	*concat_path(const char *dir, const char *cmd);
//void	handle_input_redir(t_redirs *redirs);
void	process_input(t_gen *gen, t_redirs *redirs, char *input);
void	init_structs(t_gen **gen, t_redirs **redirs);
t_command	*create_new_command(char *token);
void	handle_redirections(t_command *new_cmd, char *arg, char **saveptr2);
void	add_command_to_list(t_command **head, t_command **current, t_command *new_cmd);
void	parse_arguments(t_command *new_cmd, char *token);

// parsing 

char	*ft_strtok_r(char *str, const char *delim, char **saveptr);	// Dzieli delimiterem zdanie 
size_t	ft_strcspn(const char *str, const char *delim);
size_t ft_strspn(const char *str, const char *delim);
t_command *parse_command(char *input);

// pipex

void	init_pipes(t_gen *gen);
char	*find_path(char *cmd1, char **envp);
int     execute_pipeline(t_command *command, t_gen *gen, t_redirs *redirs);
void	create_child_processes(t_command *command, t_gen *gen);
void	ft_child_process(t_command *command, t_gen *gen, int i);
void    ft_read_fd(t_command *command, t_gen *gen, int i);
void    ft_write_fd(t_command *command, t_gen *gen, int i);
void	close_pipes(t_gen *gen);

// redirections

void	handle_input_redir(t_redirs *redirs, char **saveptr2);
void	handle_heredoc(t_redirs *redirs, char **saveptr2);
void	handle_output_redir(t_redirs *redirs, char **saveptr2);
void	handle_append_redir(t_redirs *redirs, char **saveptr2);

// history

void ft_history_list(t_gen *gen, char *input);
void ft_display_history_list(t_gen *gen);

// utils

void free_command(t_command *command);
int	ft_count_cmds(t_command *command);
void    print_error(char *cmd);
void	ft_error(char *str);
int	if_whitespace(char *str);



// void    builtin_env(void);
// void    init_global_envp(char **envp);
// void    ft_env(char **envp);

#endif
