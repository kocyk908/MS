/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:02:12 by lkoc              #+#    #+#             */
/*   Updated: 2024/08/20 00:54:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_cd(t_arg *args)
{
	char	*home_dir;
	int		i;

	i = 0;
	while (args[i].arg)
		i++;
	cd_too_many(i);
	if (i > 2)
		return ;
	if (!args[1].arg)
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
		if (chdir(args[1].arg) != 0)
			printf("cd: %s: No such file or directory\n", args[1].arg);
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

void	builtin_exit(t_arg *args)
{
	int	i;

	printf("exit\n");
	i = 0;
	while (args[i].arg)
		i++;
	if (i == 2)
	{
		if (digits_only(args[1].arg))
			exit(ft_atoi(args[1].arg));
		else
		{
			printf("bash: exit: %s: numeric argument required\n", args[1].arg);
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
	if (ft_strcmp(command->args[0].arg, "echo") == 0)
		builtin_echo(command->args, &command->redirs, gen);
	else if (ft_strcmp(command->args[0].arg, "cd") == 0)
		builtin_cd(command->args);
	else if (ft_strcmp(command->args[0].arg, "pwd") == 0)
		builtin_pwd();
	else if (ft_strcmp(command->args[0].arg, "exit") == 0)
		builtin_exit(command->args);
	else if (ft_strcmp(command->args[0].arg, "unset") == 0)
		ft_unset_env(gen, command->args[1].arg);
	else if (ft_strcmp(command->args[0].arg, "history") == 0)
		ft_display_history_list(gen);
	else if (ft_strcmp(command->args[0].arg, "export") == 0)
		ft_export_env(gen, command->args[1].arg);
}

int	is_builtin(char *cmd)
{
	return ((ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
			|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "exit") == 0)
		|| (ft_strcmp(cmd, "history") == 0) || (ft_strcmp(cmd, "export") == 0)
		|| (ft_strcmp(cmd, "unset") == 0));
}
