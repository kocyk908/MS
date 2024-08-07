#include "minishell.h"

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
		command->path = find_path(command->args[0], gen);
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
