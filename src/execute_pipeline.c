#include "minishell.h"
#include <sys/types.h>
#include <sys/stat.h>

void	ft_read_fd(t_command *command, t_gen *gen, int i)
{
	int	j;

	j = 0;
	if ((i == 0) && (command->redirs.input_redir > 0))
		if (dup2(command->redirs.input_redir, 0) == -1)
			perror("Error!");
	if (i > 0)
		if (dup2(gen->pipes[i - 1][0], 0) == -1)
			perror("Error!");
	while (j < gen->num_of_cmds - 1)
	{
		if (j != (i - 1))
			close(gen->pipes[j][0]);
		j++;
	}
}

void	ft_write_fd(t_command *command, t_gen *gen, int i)
{
	int	j;

	if (i < gen->num_of_cmds - 1)
		if (dup2(gen->pipes[i][1], 1) == -1)
			perror("Error!");
	if ((i == gen->num_of_cmds - 1) && (command->redirs.output_redir > 0))
		if (dup2(command->redirs.output_redir, 1) == -1)
			perror("Error!");
	j = 0;
	while (j < gen->num_of_cmds - 1)
	{
		if (j != i)
			close(gen->pipes[j][1]);
		j++;
	}
}

void check_stdout_pipe(void)
{
    struct stat st;
    if (fstat(STDOUT_FILENO, &st) == -1) {
        perror("fstat");
        return;
    }

    if (S_ISFIFO(st.st_mode))
        fprintf(stderr, "stdout is connected to a pipe or FIFO\n");
    else
        fprintf(stderr, "stdout is not connected to a pipe\n");
}

char    **convert_args(t_arg *args)
{
    int i;
    int count;
    char    **argv;

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


void ft_child_process(t_command *command, t_gen *gen, int i)
{
    char **argv;

    argv = convert_args(command->args);
    ft_read_fd(command, gen, i);
    ft_write_fd(command, gen, i);
    if (execve(command->path, argv, gen->envs) == -1)
    {
        printf("%s: command not found\n", command->args[0].arg);
        exit(127);
    }
   free(argv);
}


// void ft_child_process(t_command *command, t_gen *gen, int i)
// {
//     char **argv;

//     argv = convert_args(command->args);
//     ft_read_fd(command, gen, i);
//     ft_write_fd(command, gen, i);
//     if (is_builtin(command->args[0].arg))
//     {
//         execute_builtin(command, gen);
//         close_pipes(gen);
//         exit(gen->exit_status);
//     }
//     else
//     {
//         if (execve(command->path, argv, gen->envs) == -1)
//         {
//             printf("%s: command not found\n", command->args[0].arg);
//             exit(127);
//         }
//     }
//     free(argv);
// }

int	execute_pipeline(t_command *command, t_gen *gen)
{
	int	i;
	int	status;

	gen->pipes = malloc((gen->num_of_cmds - 1) * sizeof(int *));
	init_pipes(gen);
	gen->pids = malloc((gen->num_of_cmds + 1) * sizeof(int));
	create_child_processes(command, gen);
	close_pipes(gen);
	if (command->redirs.is_heredoc)
		unlink("heredoc.txt");
	i = 0;
	while (i < gen->num_of_cmds)
	{
		wait(&status);
		gen->exit_status = WEXITSTATUS(status);
		i++;
	}
    gen->is_blocking = 0;
	return (0);
}
