#include "minishell.h"

int ft_strlen_env(char *str, char c)
{
	int i;

	i = 0;
	while(str[i] != c)
		i++;
	return (i);
}

void ft_env_val_vol2(t_gen *gen, char *trimmed_env)
{
	int i;
	int j;
	int len_env;
	char *env;

	i = 0;
	while(gen->envs[i])
	{
		if(ft_strchr(gen->envs[i], '='))
		{
			j = 0;
			len_env = ft_strlen_env(gen->envs[i], '=');
			env = malloc(sizeof(char) * len_env + 1);
			while(gen->envs[i][j] != '=')
			{
				env[j] = gen->envs[i][j];
				j++;
			}
			env[j] = '\0';
			if(!ft_strcmp(trimmed_env, env))
				printf("%s\n", ft_strrchr(gen->envs[i], '=') + 1);
				free(env);
		}
		i++;
	}
}

void ft_env_val(t_gen *gen, char *str)
{
	char *trimmed_env;
	int len_env;
	int i;

	trimmed_env = malloc(sizeof(char) * ft_strlen(str));
	i = 0;
	while(str[i + 1])
	{
		trimmed_env[i] = str[i+1];
		i++;
	}
	trimmed_env[i] = '\0';
	if(!ft_strcmp(trimmed_env, "?"))
	{
		// printf("-%d-\n", gen->exit_status);
	}
	ft_env_val_vol2(gen, trimmed_env);
	free(trimmed_env);
}

void	builtin_echo(char **args, t_redirs *redirs, t_gen *gen)
{
	int		i;
	int		j;
	int		fd;
	bool	n;
	
	fd = 1;
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
	if (redirs->is_append || redirs->output_redir != -1)
		fd = redirs->output_redir;
	else
		fd = STDOUT_FILENO;
	while (args[i])
	{
		if (args[i][0] == '$')
		{
			// printf("print env var:");
			ft_env_val(gen, args[i]); //not sure jak chcesz do tego podejść to zostawie tak narazie
		}
		else
			ft_putstr_fd(args[i], fd);
		if (args[i + 1])
			ft_putstr_fd(" ", fd);
		i++;
	}
	if (!n || redirs->is_append)
		ft_putstr_fd("\n", fd);
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
