#include "minishell.h"

int	ft_count_cmds(t_command *command)
{
	t_command	*temp;
	int			i;

	temp = command;
	i = 0;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

void	ft_child_process(t_command *command, t_gen *gen, t_redirs *redirs,
		int i, char **envp)
{
	int	input;
	int	ouput;
	int	j;

	input = 0;
	ouput = 1;
	if (i == 0)
	{
		printf("%d process, read from fd %d\n", i, command->redirs.input_redir);
		if (dup2(command->redirs.input_redir, 0) == -1)
			ft_error("Unable to change fd");
	}
	if (i > 0)
	{
		printf("%d process, read from fd %d\n", i, gen->pipes[i - 1][0]);
		if (dup2(gen->pipes[i - 1][0], 0) == -1)
			ft_error("Unable to change fd");
	}
	j = 0;
	while (j < gen->num_of_cmds - 1)
	{
		if (j != (i - 1))
		{
			printf("%d process, closing read end %d\n", i, gen->pipes[j][0]);
			close(gen->pipes[j][0]);
		}
		j++;
	}
	if (i < gen->num_of_cmds - 1)
	{
		printf("%d process, write to fd %d\n", i, gen->pipes[i][1]);
		if (dup2(gen->pipes[i][1], 1) == -1)
			ft_error("Unable to change fd");
	}
	if (i == gen->num_of_cmds - 1)
	{
		printf("%d process, write to fd %d\n", i, ouput);
		if (dup2(ouput, 1) == -1)
			ft_error("Unable to change fd");
	}
	j = 0;
	while (j < gen->num_of_cmds - 1)
	{
		if (j != i)
		{
			printf("%d process, closing write end %d\n", i, gen->pipes[j][1]);
			close(gen->pipes[j][1]);
		}
		j++;
	}
	printf("--ok\n");
	execve(command->path, command->args, envp); // need path
}

int	execute_pipeline(t_command *command, t_gen *gen,
			t_redirs *redirs, char **envp)
{
	int	i;

	gen->num_of_cmds = ft_count_cmds(command);
	printf("num of commands: %d\n", gen->num_of_cmds);
	if (redirs->input_redir1)
		handle_input_redir(redirs, NULL);
	gen->pipes = malloc((gen->num_of_cmds - 1) * sizeof(int *));
	init_pipes(gen);
	gen->pids = malloc((gen->num_of_cmds + 1) * sizeof(int));
	create_child_processes(command, gen, redirs, envp);
	close_pipes(gen);
	i = 0;
	while (i < gen->num_of_cmds)
	{
		wait(NULL);
		i++;
	}
	return (0);
}
