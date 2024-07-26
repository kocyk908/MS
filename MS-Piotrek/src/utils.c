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

int	if_whitespace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}