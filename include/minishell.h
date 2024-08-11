#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_arg
{
    char *arg;
    bool in_quotes;
	bool ignore_pipe;
	bool is_first;
} t_arg;

typedef struct s_redirs
{
	int					input_redir;
	int					is_heredoc;
	int					output_redir;
	int					is_append;
}						t_redirs;

typedef struct s_command
{
	char				*path;
	t_arg				*args;
	t_redirs			redirs;
	struct s_command	*next;
}						t_command;

typedef struct s_history
{
	int					num;
	char				*input;
	struct s_history	*next;
}						t_history;

typedef struct s_gen
{
	int					num_of_cmds;
	int					**pipes;
	int					*pids;
	int					is_path;
	int					exit_status;
	char				**envs;
	t_history			*history;
}						t_gen;

void					process_input(t_gen *gen, char *input);
void					init_structs(t_gen **gen, t_redirs **redirs);
t_command				*create_new_command(char *token);
void					add_command_to_list(t_command **head,
							t_command **current, t_command *new_cmd);

// parsing

char					*ft_strtok_r(char *str, const char *delim,
							char **saveptr, t_arg *args);
// Dzieli delimiterem zdanie
size_t					ft_strcspn(const char *str, const char *delim);
size_t					ft_strspn(const char *str, const char *delim);
t_command				*parse_command(char *input);
void					parse_arguments(t_command *new_cmd, char *token);

// pipex

void					init_pipes(t_gen *gen);
char					*find_path(char *cmd1, t_gen *gen);
int						execute_pipeline(t_command *command, t_gen *gen);
void					create_child_processes(t_command *command, t_gen *gen);
void					ft_child_process(t_command *command, t_gen *gen, int i);
void					ft_read_fd(t_command *command, t_gen *gen, int i);
void					ft_write_fd(t_command *command, t_gen *gen, int i);
void					close_pipes(t_gen *gen);

// redirections

void					handle_input_redir(t_redirs *redirs, char **saveptr2);
void					ft_handle_heredoc_vol2(char *arg, char *temp, int fd);
void					ft_handle_heredoc_vol3(char *temp, int fd);
void					handle_heredoc(t_redirs *redirs, char **saveptr2);
void					handle_output_redir(t_redirs *redirs, char **saveptr2);
void					handle_append_redir(t_redirs *redirs, char **saveptr2);
void					handle_redirections(t_command *new_cmd, char *arg,
							char **saveptr2);

// history

void					ft_history_list(t_gen *gen, char *input);
void					ft_display_history_list(t_gen *gen);

// utils

int						ft_count_cmds(t_command *command);
void					print_error(char *cmd);
int						if_whitespace(char *str);
int						digits_only(char *str);
void					ft_copy_arr(char **dest, char **src, int arr_len);
int						ft_strlen_env(char *str, char c);

// free

void					free_command(t_command *command);
void					ft_free_arr(char **arr);
void					ft_free_pipes(t_gen *gen);
void					ft_free_path(t_command *command);
void					ft_free_history(t_history *node);

// build-ins

int						is_builtin(char *cmd);
void					execute_builtin(t_command *command, t_gen *gen);
void					ft_export_env(t_gen *gen, char *env);
void					ft_buildin_echo_vol3(t_gen *gen, t_arg *args, int fd,
							int i);
void					ft_buildin_echo_vol2(t_arg *args, int *i, bool *n);
void					builtin_echo(t_arg *args, t_redirs *redirs, t_gen *gen);
void					builtin_cd(t_arg *args);
void					builtin_pwd(void);
void					builtin_exit(t_arg *args);

// envp

void					ft_env_val(t_gen *gen, char *str, int fd);
void					ft_env_val_vol3(char *env, char *trimmed_env, int fd);
void					ft_env_val_vol2(t_gen *gen, char *trimmed_env, int fd, int i);
void					ft_export_env(t_gen *gen, char *env);
void					ft_copy_envp(t_gen *gen, char **envp);
void					ft_unset_env(t_gen *gen, char *env);
char					**ft_unset_env_vol2(t_gen *gen, char *env, int env_len);
bool					ft_env_cmp(t_gen *gen, char *env);

// signal

void					signal_d(void);
void					signal_c(int sig);
void					init_signals(void);


void wypisanko(char *token, char *input);

#endif
