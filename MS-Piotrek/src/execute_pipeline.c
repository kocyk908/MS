#include "minishell.h"

void	ft_error(char *str)
{
	printf("%s\n", str); // place perror
}

int ft_count_cmds(t_command *command)
{
	t_command	*temp;
	int i;

	temp = command;
	i = 0;
	while(temp)
	{
		temp = temp->next;
		i++;
	}
	return i;
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
		printf("%d process, read from fd %d\n", i, redirs->input_redir);
		if (dup2(redirs->input_redir, 0) == -1)
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

int	execute_pipeline(t_command *command, t_gen *gen, t_redirs *redirs,
		char **envp)
{
	int		i;
	int		id;

	gen->num_of_cmds = ft_count_cmds(command);
	printf("num of commands%d\n", gen->num_of_cmds);
	// to remove
	if (redirs->input_redir1)
	{
		redirs->input_redir = open(redirs->input_redir1, O_RDONLY);
		if (redirs->input_redir == -1)
			ft_error("Unable to open a file");
	}
	i = 0;
	gen->pipes = malloc((gen->num_of_cmds - 1) * sizeof(int *)); // to free
	while (i < gen->num_of_cmds - 1)
	{
		gen->pipes[i] = malloc(2 * sizeof(int)); // to free
		if (pipe(gen->pipes[i]) == -1)
			ft_error("Unable to create pipe");
		printf("pipe created, read %d, write %d\n", gen->pipes[i][0],
			gen->pipes[i][1]);
		i++;
	}
	i = 0;
	gen->pids = malloc((gen->num_of_cmds + 1) * sizeof(int)); // to free
	i = 0;
	while (command)
	{
		command->path = find_path(command->args[0], envp);
		printf("path to cmd1: %s\n", command->args[0]);
		printf("path to cmd1: %s\n", command->path);

		gen->pids[i] = fork();
		if (gen->pids[i] == 0)
		{
			ft_child_process(command, gen, redirs, i, envp); // finished here
			return (0);
		}
		command = command->next;
		i++;

	}
	for (i = 0; i < gen->num_of_cmds - 1; i++)
	{
		close(gen->pipes[i][0]);
		close(gen->pipes[i][1]);
        // close redirs
	}
	i = 0;
	while (i < gen->num_of_cmds)
	{
		wait(NULL);
		i++;
	}
	return (0);
}
