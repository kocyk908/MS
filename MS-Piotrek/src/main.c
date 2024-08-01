#include "minishell.h"

int	is_builtin(char *cmd)
{
	return ((ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
			|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "exit") == 0)
		|| (ft_strcmp(cmd, "history") == 0) || (ft_strcmp(cmd, "export") == 0)
		|| (ft_strcmp(cmd, "unset") == 0));
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

int	check_unclosed_quotes(char *input)
{
	int	single_quote_open;
	int	double_quote_open;
	int	i;

	single_quote_open = 0;
	double_quote_open = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !double_quote_open)
			single_quote_open = !single_quote_open;
		else if (input[i] == '"' && !single_quote_open)
			double_quote_open = !double_quote_open;
		i++;
	}
	if (single_quote_open || double_quote_open)
		return (1);
	return (0);
}

// void print_parsed_arguments(t_command *cmd_list)
// {
// 	t_command *cmd = cmd_list;
//     int i;

//     while (cmd)
//     {
//         printf("Command:\n");
//         i = 0;
//         while (cmd->args[i])
//         {
//             printf("  Arg[%d]: %s\n", i, cmd->args[i]);
//             i++;
//         }
//         printf("  Input redir: %d\n", cmd->redirs.input_redir);
//         printf("  Output redir: %d\n", cmd->redirs.output_redir);
//         printf("  Is append: %d\n", cmd->redirs.is_append);
//         printf("  Is heredoc: %d\n", cmd->redirs.is_heredoc);
//         cmd = cmd->next;
//     }
// }

void	process_input(t_gen *gen, char *input)
{
	t_command	*cmd_list;

	add_history(input);
	if (check_unclosed_quotes(input))
	{
		printf("Error: unclosed quotes\n");
		gen->exit_status = 1;
		return ;
	}
	ft_history_list(gen, input);
	cmd_list = parse_command(input);
	if (!cmd_list->args[0]) // case for missing arg before < or <<
		return ;
	//print_parsed_arguments(cmd_list);
	gen->num_of_cmds = ft_count_cmds(cmd_list);
	if (cmd_list && is_builtin(cmd_list->args[0]))
		execute_builtin(cmd_list, gen);
	else
		if (gen->isPath == 1)
			ft_free_path(cmd_list);
		ft_free_pipes(gen);
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
		else if (!input) // Obsługa CTRL+D
			signal_d();
		else
			free(input);
	}
	ft_free_arr(gen->envs);
	// ft_free_history(gen->history);
	return (0);
}
