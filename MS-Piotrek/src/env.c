#include "minishell.h"

// char	**g_envp;

// void	init_global_envp(char **envp)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (envp[i] != NULL)
// 		i++;
// 	g_envp = malloc((i + 1) * sizeof(char *));
// 	while (j < i)
// 	{
// 		g_envp[j] = strdup(envp[j]);
// 		j++;
// 	}
// 	g_envp[i] = NULL;
// }

// void	ft_env(char **envp)
// {
// 	pid_t	pid;
// 	char	*args[2];
// 	int		status;

// 	args[0] = "env";
// 	args[1] = NULL;
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		perror("fork");
// 		return ;
// 	}
// 	if (pid == 0)
// 	{
// 		if (execve("/usr/bin/env", args, envp) == -1)
// 		{
// 			perror("execve");
// 			exit(1);
// 		}
// 	}
// 	else
// 	{
// 		waitpid(pid, &status, 0);
// 	}
// }

// void	builtin_env(void)
// {
// 	int	i;

// 	i = 0;
// 	while (g_envp[i] != NULL)
// 	{
// 		printf("%s\n", g_envp[i]);
// 		i++;
// 	}
// }
