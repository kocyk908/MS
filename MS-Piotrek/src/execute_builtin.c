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
	while (args[i])
    {
        printf("%s", args[i]);
        if (args[i + 1])
            printf(" ");
        i++;
    }
	if (n == false)
		printf("\n");
}

void	builtin_cd(char **args)
{
	char	*home_dir;
	char	cwd[1024]; //max długość ścieżki, wystrczający dla getcwd

	if (!args[1])
	{
		home_dir = getenv("HOME");
		if (home_dir)
		{
			if (chdir(home_dir) != 0)
				perror("cd failed");
		}
		else
			printf("cd: HOME not set\n");
	}
	else
	{
		if (chdir(args[1]) != 0)
			perror("cd failed");
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("getcwd failed");
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
	// można podać exit sam -> robi exit i pisze exit
	// można podać exit i numer -> robi exit i pisze exit
	// mozna podać exit i coś innego niż numer -> robi exit i pisze bash: exit: {to co sie napisało}: numeric argument required
}

void	execute_builtin(t_command *command, char **envp)
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
