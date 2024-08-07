#include "minishell.h"

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
	char	cwd[4096];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
	}
	else
	{
		perror("getcwd failed");
	}
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
			exit(255);
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

void	execute_builtin(t_command *command, t_gen *gen)
{
	if (ft_strcmp(command->args[0], "echo") == 0)
		builtin_echo(command->args, &command->redirs, gen);
	else if (ft_strcmp(command->args[0], "cd") == 0)
		builtin_cd(command->args);
	else if (ft_strcmp(command->args[0], "pwd") == 0)
		builtin_pwd();
	else if (ft_strcmp(command->args[0], "exit") == 0)
		builtin_exit(command->args);
	else if (ft_strcmp(command->args[0], "unset") == 0)
		ft_unset_env(gen, command->args[1]);
	else if (ft_strcmp(command->args[0], "history") == 0)
		ft_display_history_list(gen);
	else if (ft_strcmp(command->args[0], "export") == 0)
		ft_export_env(gen, command->args[1]);
}
