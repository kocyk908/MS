#include "minishell.h"

void builtin_echo(char **args) {
    for (int i = 1; args[i]; i++) {
        if (i > 1) {
            printf(" ");
        }
        printf("%s", args[i]);
    }
    printf("\n");
}

void builtin_cd(char **args) {
    if (args[1]) {
        if (chdir(args[1]) != 0) {
            perror("cd failed");
        }
    }
}

void builtin_pwd() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("getcwd failed");
    }
}

void builtin_exit() {
    exit(0);
}

void execute_builtin(t_command *command) {
    if (strcmp(command->args[0], "echo") == 0) {
        builtin_echo(command->args);
    } else if (strcmp(command->args[0], "cd") == 0) {
        builtin_cd(command->args);
    } else if (strcmp(command->args[0], "pwd") == 0) {
        builtin_pwd();
    } else if (strcmp(command->args[0], "exit") == 0) {
        builtin_exit();
    }
}

