#include "minishell.h"

void	builtin_echo(char **args)
{
	int		i;
	int		j;
	bool	n;

	i = 1; // bo 0 to echo
	n = false;
	while (args[i] && args[i][0] == '-')
	{
		j = 1;
		while (args[i][j] == 'n') // -n -nn -nnnnn może być więcej
			j++;
		if (args[i][j] == '\0') // nie może być -nnnk
		{
			n = true;
			i++;
		}
		else
			break ;
	}
	while (i >= 1)
		printf("%s", args[i]);
	if (n == false)
		printf("\n");
}

void	builtin_cd(char **args)
{
	if (args[1])
	{
		if (chdir(args[1]) != 0)
		{
			perror("cd failed");
		}
	}
}

void	builtin_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
	}
	else
	{
		perror("getcwd failed");
	}
}

void	builtin_exit(void)
{
	exit(0);
}

void	execute_builtin(t_command *command)
{
	if (strcmp(command->args[0], "echo") == 0)
	{
		builtin_echo(command->args);
	}
	else if (strcmp(command->args[0], "cd") == 0)
	{
		builtin_cd(command->args);
	}
	else if (strcmp(command->args[0], "pwd") == 0)
	{
		builtin_pwd();
	}
	else if (strcmp(command->args[0], "exit") == 0)
	{
		builtin_exit();
	}
}
