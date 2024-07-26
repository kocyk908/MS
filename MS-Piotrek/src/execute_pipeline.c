#include "minishell.h"

void ft_read_fd(t_command *command, t_gen *gen, int i)
{
	int	j;

	j = 0;
	if ((i == 0) && (command->redirs.input_redir > 0))
		if (dup2(command->redirs.input_redir, 0) == -1)
			ft_error("Unable to change fd-1");
	if (i > 0)
		if (dup2(gen->pipes[i - 1][0], 0) == -1)
			ft_error("Unable to change fd-2");
	while (j < gen->num_of_cmds - 1)
	{
		if (j != (i - 1))
			close(gen->pipes[j][0]);
		j++;
	}
}

void ft_write_fd(t_command *command, t_gen *gen, int i)
{
	int	j;

	if (i < gen->num_of_cmds - 1)
		if (dup2(gen->pipes[i][1], 1) == -1)
			ft_error("Unable to change fd-3");
	if ((i == gen->num_of_cmds - 1) && (command->redirs.output_redir > 0))
		if (dup2(command->redirs.output_redir, 1) == -1)
			ft_error("Unable to change fd-4");
	j = 0;
	while (j < gen->num_of_cmds - 1)
	{
		if (j != i)
			close(gen->pipes[j][1]);
		j++;
	}
}

void	ft_child_process(t_command *command, t_gen *gen,
		int i)
{
	ft_read_fd(command, gen, i);
	ft_write_fd(command, gen, i);
	if(execve(command->path, command->args, gen->envs) == -1); 
			perror("Error!");
}

int	execute_pipeline(t_command *command, t_gen *gen,
			t_redirs *redirs)
{
	int	i;

	gen->pipes = malloc((gen->num_of_cmds - 1) * sizeof(int *));
	init_pipes(gen);
	gen->pids = malloc((gen->num_of_cmds + 1) * sizeof(int));
	create_child_processes(command, gen);
	close_pipes(gen);
	if(command->redirs.is_heredoc)
		unlink("heredoc.txt");
	i = 0;
	while (i < gen->num_of_cmds)
	{
		wait(NULL);
		i++;
	}
	return (0);
}
