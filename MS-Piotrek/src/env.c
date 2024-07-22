#include "minishell.h"

char **global_envp;

void init_global_envp(char **envp)
{
    int i;
    for (i = 0; envp[i] != NULL; i++);
    global_envp = malloc((i + 1) * sizeof(char *));
    for (int j = 0; j < i; j++)
    {
        global_envp[j] = strdup(envp[j]);
    }
    global_envp[i] = NULL;
}

void ft_env(char **envp)
{
    pid_t pid;
    char *args[2];
    int status;

    args[0] = "env";
    args[1] = NULL;
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return;
    }
    if (pid == 0)
    {
        if (execve("/usr/bin/env", args, envp) == -1)
        {
            perror("execve");
            exit(1);
        }
    }
    else
    {
        waitpid(pid, &status, 0);
    }
}

void builtin_env(void)
{
    for (int i = 0; global_envp[i] != NULL; i++)
    {
        printf("%s\n", global_envp[i]);
    }
}