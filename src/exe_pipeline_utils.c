/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipeline_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:02:12 by pruszkie          #+#    #+#             */
/*   Updated: 2024/08/13 23:25:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**convert_args(t_arg *args)
{
	int		i;
	int		count;
	char	**argv;

	i = 0;
	count = 0;
	while (args[count].arg)
		count++;
	argv = malloc((count + 1) * sizeof(char *));
	if (!argv)
		exit(EXIT_FAILURE);
	while (i < count)
	{
		argv[i] = args[i].arg;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

void	init_pipes(t_gen *gen)
{
	int	i;

	i = 0;
	while (i < gen->num_of_cmds - 1)
	{
		gen->pipes[i] = malloc(2 * sizeof(int));
		if (pipe(gen->pipes[i]) == -1)
			perror("Error!");
		i++;
	}
}

void	close_pipes(t_gen *gen)
{
	int	i;

	i = 0;
	while (i < gen->num_of_cmds - 1)
	{
		close(gen->pipes[i][0]);
		close(gen->pipes[i][1]);
		i++;
	}
}

void	create_child_processes(t_command *command, t_gen *gen)
{
	int	i;

	i = 0;
	while (command)
	{
		command->path = find_path(command->args[0].arg, gen);
		gen->pids[i] = fork();
		if (gen->pids[i] == 0)
		{
			ft_child_process(command, gen, i);
			exit(0);
		}
		command = command->next;
		i++;
	}
}
