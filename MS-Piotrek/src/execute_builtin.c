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
}

void	builtin_pwd(void)
{
	char	cwd[4096]; //max path sprawdzone _PC_PATH_MAX - przynajmniej na kompie w 42

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
	}
	else
	{
		perror("getcwd failed");
	}
}
/////////// do exit

int	digits_only(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (i != 0 && str[i] == '-')
			return (0);
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	builtin_exit(char **args)
{
	int	i;

	printf("exit\n");
	i = 0;
	while (args[i])
		i++;
	if (i == 2)
	{
		if (digits_only(args[1]))
			exit(ft_atoi(args[1]));
		else
		{
			printf("bash: exit: %s: numeric argument required\n", args[1]);
			exit (255);
		}
	}
	else if (i > 2)
	{
		printf("bash: exit: too many arguments\n");
		return ;
	}
	else
		exit(0);
}

void	execute_builtin(t_command *command, char **envp)
{
	if (ft_strcmp(command->args[0], "echo") == 0)
		builtin_echo(command->args);
	else if (ft_strcmp(command->args[0], "cd") == 0)
		builtin_cd(command->args);
	else if (ft_strcmp(command->args[0], "pwd") == 0)
		builtin_pwd();
	else if (ft_strcmp(command->args[0], "exit") == 0)
		builtin_exit(command->args);
	//else if (ft_strcmp(command->args[0], "export") == 0)
	//	builtin_export(command->args);
	//else if (ft_strcmp(command->args[0], "unset") == 0)
	//	builtin_unset(command->args);
	// else if (ft_strcmp(command->args[0], "env") == 0)
	// 	builtin_env();
}
