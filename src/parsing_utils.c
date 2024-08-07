#include "minishell.h"

t_command	*create_new_command(char *token)
{
	t_command	*new_cmd;

	(void)token;
	new_cmd = malloc(sizeof(t_command));
	if (!new_cmd)
		return (NULL);
	new_cmd->args = malloc(64 * sizeof(char *));
	if (!new_cmd->args)
		return (NULL);
	new_cmd->redirs.input_redir = -1;
	new_cmd->redirs.output_redir = -1;
	new_cmd->redirs.is_append = 0;
	new_cmd->redirs.is_heredoc = 0;
	new_cmd->next = NULL;
	return (new_cmd);
}

void	handle_redirections(t_command *new_cmd, char *arg, char **saveptr2)
{
	if (ft_strncmp(arg, "<", ft_strlen(arg)) == 0)
	{
		handle_input_redir(&new_cmd->redirs, saveptr2);
	}
	else if (ft_strncmp(arg, "<<", ft_strlen(arg)) == 0)
	{
		handle_heredoc(&new_cmd->redirs, saveptr2);
	}
	else if (ft_strncmp(arg, ">", ft_strlen(arg)) == 0)
	{
		handle_output_redir(&new_cmd->redirs, saveptr2);
	}
	else if (ft_strncmp(arg, ">>", ft_strlen(arg)) == 0)
	{
		handle_append_redir(&new_cmd->redirs, saveptr2);
	}
}

void	add_command_to_list(t_command **head, t_command **current,
		t_command *new_cmd)
{
	if (!(*head))
	{
		*head = new_cmd;
		*current = new_cmd;
	}
	else
	{
		(*current)->next = new_cmd;
		*current = new_cmd;
	}
}

void	parse_arguments(t_command *new_cmd, char *token)
{
	char	*arg;
	char	*saveptr2;
	int		i;

	i = 0;
	arg = ft_strtok_r(token, " ", &saveptr2);
	while (arg != NULL)
	{
		handle_redirections(new_cmd, arg, &saveptr2);
		if (ft_strcmp(arg, "<") != 0 && ft_strcmp(arg, "<<") != 0
			&& ft_strcmp(arg, ">") != 0 && ft_strcmp(arg, ">>") != 0)
		{
			new_cmd->args[i++] = arg;
		}
		arg = ft_strtok_r(NULL, " ", &saveptr2);
	}
	new_cmd->args[i] = NULL;
}
