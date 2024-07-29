#include "minishell.h"

int	is_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "exit") == 0)
		|| (ft_strcmp(cmd, "history") == 0) || (ft_strcmp(cmd, "export") == 0) 
		|| (ft_strcmp(cmd, "unset") == 0);
}

void	init_structs(t_gen **gen, t_redirs **redirs)
{
	*gen = malloc(sizeof(t_gen));
	*redirs = malloc(sizeof(t_redirs));
	(*gen)->history = NULL; 

	if (!(*gen) || !(*redirs))
	{
		if (*gen)
			free(*gen);
		if (*redirs)
			free(*redirs);
		exit(EXIT_FAILURE);
	}
}

void	process_input(t_gen *gen, char *input)
{
	t_command	*cmd_list;

	add_history(input);
	ft_history_list(gen, input);

	cmd_list = parse_command(input);

	if(!cmd_list->args[0]) // case for missing arg before < or <<
		return;
	gen->num_of_cmds = ft_count_cmds(cmd_list);

	if (cmd_list && is_builtin(cmd_list->args[0]))
		execute_builtin(cmd_list, gen);
	else
	{
		execute_pipeline(cmd_list, gen);
		ft_free_path(cmd_list);
		free(gen->pipes);
		free(gen->pids);
	}
	free_command(cmd_list);
}

int	main(int ac, char **av, char **envp)
{
	char		*input;
	t_gen		*gen;
	t_redirs	*redirs;

	(void)ac;
	(void)av;
	init_signals();
	init_structs(&gen, &redirs);
	ft_copy_envp(gen, envp);
	while (1)
	{
		input = readline("msh> ");
		if (input && *input != '\0' && !if_whitespace(input))
		{
			process_input(gen, input);
			free(input);
		}
		else if (!input)  // Obsługa CTRL+D
			signal_d();
		else
			free(input);
	}
	ft_free_arr(gen->envs);
	// ft_free_history(gen->history);
	return (0);
}