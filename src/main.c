/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:02:12 by lkoc              #+#    #+#             */
/*   Updated: 2024/09/07 12:57:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_structs(t_gen **gen, t_redirs **redirs, char **av, int ac)
{
	(void)ac;
	(void)av;
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

int	check_unclosed_quotes(t_gen *gen, char *input)
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
	{
		printf("Error: unclosed quotes\n");
		gen->exit_status = 1;
		return (1);
	}
	return (0);
}

void	process_input(t_gen *gen, char *input)
{
	t_command	*cmd_list;

	add_history(input);
	if (check_unclosed_quotes(gen, input))
		return ;
	ft_history_list(gen, input);
	cmd_list = parse_command(gen, input);
	if (!cmd_list->args[0].arg)
		return ;
	gen->num_of_cmds = ft_count_cmds(cmd_list);
	if (gen->num_of_cmds == 1 && is_builtin(cmd_list->args[0].arg) && cmd_list)
		execute_builtin(cmd_list, gen);
	else
	{
		init_signals_duo();
		execute_pipeline(cmd_list, gen);
		init_signals();
		if (gen->is_path == 1)
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

	init_structs(&gen, &redirs, av, ac);
	init_signals();
	ft_copy_envp(gen, envp);
	while (1)
	{
		input = readline("msh> ");
		if (input && *input != '\0' && !if_whitespace(input))
		{
			process_input(gen, input);
			free(input);
		}
		else if (!input)
			signal_d();
		else
			free(input);
	}
	ft_free_arr(gen->envs);
	ft_free_history(gen->history);
	return (0);
}

// void	print_parsed_arguments(t_command *cmd_list)
// {
// 	t_command	*cmd;
// 	int			i;

// 	cmd = cmd_list;
// 	while (cmd)
// 	{
// 		printf("Command:\n");
// 		i = 0;
// 		while (cmd->args[i].arg)
// 		{
// 			printf("  Arg[%d]: %s\n", i, cmd->args[i].arg);
// 			i++;
// 		}
// 		cmd = cmd->next;
// 	}
// }