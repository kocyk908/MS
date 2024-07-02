#include "minishell.h"

// Nasza implementacja strtok_r
char *ft_strtok_r(char *str, const char *delim, char **saveptr) {
    char *end;

    if (str == NULL)
        str = *saveptr;

    if (*str == '\0') {
        *saveptr = str;
        return NULL;
    }

    // Przesuwanie wskaźnika str do pierwszego znaku niebędącego delimitorem
    str += strspn(str, delim);
    if (*str == '\0') {
        *saveptr = str;
        return NULL;
    }

    // Znajdowanie końca tokenu
    end = str + strcspn(str, delim);
    if (*end == '\0') {
        *saveptr = end;
        return str;
    }

    *end = '\0';
    *saveptr = end + 1;
    return str;
}

t_command *parse_command(char *input) {
    t_command *head = NULL;
    t_command *current = NULL;
    char *token;
    char *saveptr;
    char *arg;
    int i;

    // Tokenizacja komendy po znakach pipe'ów
    token = ft_strtok_r(input, "|", &saveptr);
    while (token != NULL) {
        t_command *new_cmd = malloc(sizeof(t_command));
        if (!new_cmd) {
            perror("malloc failed");
            exit(EXIT_FAILURE);
        }
        new_cmd->args = malloc(64 * sizeof(char *)); // Maksymalna liczba argumentów = 64
        if (!new_cmd->args) {
            perror("malloc failed");
            exit(EXIT_FAILURE);
        }
        new_cmd->redirs.input_redir = -1;
        new_cmd->redirs.output_redir = -1;
        new_cmd->redirs.is_append = 0;
        new_cmd->redirs.is_heredoc = 0;
        new_cmd->next = NULL;

        // Tokenizacja argumentów
        i = 0;
        arg = ft_strtok_r(token, " ", &saveptr);
        while (arg != NULL) {
            if (strcmp(arg, "<") == 0) {
                arg = ft_strtok_r(NULL, " ", &saveptr);
                new_cmd->redirs.input_redir = open(arg, O_RDONLY);
                if (new_cmd->redirs.input_redir == -1) {
                    perror("open failed");
                    exit(EXIT_FAILURE);
                }
            } else if (strcmp(arg, "<<") == 0) {
                arg = ft_strtok_r(NULL, " ", &saveptr);
                new_cmd->redirs.is_heredoc = 1;
                // Tu należy obsłużyć heredoc
            } else if (strcmp(arg, ">") == 0) {
                arg = ft_strtok_r(NULL, " ", &saveptr);
                new_cmd->redirs.output_redir = open(arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (new_cmd->redirs.output_redir == -1) {
                    perror("open failed");
                    exit(EXIT_FAILURE);
                }
            } else if (strcmp(arg, ">>") == 0) {
                arg = ft_strtok_r(NULL, " ", &saveptr);
                new_cmd->redirs.output_redir = open(arg, O_WRONLY | O_CREAT | O_APPEND, 0644);
                if (new_cmd->redirs.output_redir == -1) {
                    perror("open failed");
                    exit(EXIT_FAILURE);
                }
                new_cmd->redirs.is_append = 1;
            } else {
                new_cmd->args[i++] = arg;
            }
            arg = ft_strtok_r(NULL, " ", &saveptr);
        }
        new_cmd->args[i] = NULL;

        if (!head) {
            head = new_cmd;
            current = new_cmd;
        } else {
            current->next = new_cmd;
            current = new_cmd;
        }
        token = ft_strtok_r(NULL, "|", &saveptr);
    }

    return head;
}

