#include "minishell.h"

void	ft_error(char *str)
{
	printf("%s\n", str); // place perror
}

void	handle_input_redir(t_redirs *redirs)
{
	if (redirs->input_redir1)
	{
		redirs->input_redir = open(redirs->input_redir1, O_RDONLY);
		if (redirs->input_redir == -1)
			ft_error("Unable to open a file");
	}
}

void	init_pipes(t_gen *gen)
{
	int	i;

	i = 0;
	while (i < gen->num_of_cmds - 1)
	{
		gen->pipes[i] = malloc(2 * sizeof(int));
		if (pipe(gen->pipes[i]) == -1)
			ft_error("Unable to create pipe");
		printf("pipe created, read %d, write %d\n",
			gen->pipes[i][0], gen->pipes[i][1]);
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

void	create_child_processes(t_command *command, t_gen *gen,
			t_redirs *redirs, char **envp)
{
	int	i;

	i = 0;
	while (command)
	{
		command->path = find_path(command->args[0], envp);
		printf("path to cmd%d: %s\n", i + 1, command->path);
		gen->pids[i] = fork();
		if (gen->pids[i] == 0)
		{
			ft_child_process(command, gen, redirs, i, envp);
			exit(0);
		}
		command = command->next;
		i++;
	}
}
