#include "minishell.h"

void	free_command(t_command *command)
{
	t_command	*temp;

	while (command)
	{
		temp = command;
		command = command->next;
		free(temp->args);
		free(temp);
	}
}

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