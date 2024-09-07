/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoc <lkoc@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:02:12 by lkoc              #+#    #+#             */
/*   Updated: 2024/09/07 18:42:41 by lkoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (ft_strcmp(arg, "<") == 0)
	{
		handle_input_redir(&new_cmd->redirs, saveptr2);
	}
	else if (ft_strcmp(arg, "<<") == 0)
	{
		handle_heredoc(&new_cmd->redirs, saveptr2);
	}
	else if (ft_strcmp(arg, ">") == 0)
	{
		handle_output_redir(&new_cmd->redirs, saveptr2);
	}
	else if (ft_strcmp(arg, ">>") == 0)
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

void	process_argument(t_command *new_cmd, t_arg *arg_struct,
			char **saveptr2, int *i)
{
	char	*arg;

	arg = arg_struct->arg;
	if ((arg_struct->which_quotes == '\'' || arg_struct->which_quotes == '"')
		&& (ft_strcmp(arg, "<") == 0 || ft_strcmp(arg, "<<") == 0
			|| ft_strcmp(arg, ">") == 0 || ft_strcmp(arg, ">>") == 0
			|| ft_strcmp(arg, "|") == 0))
	{
		new_cmd->args[*i] = *arg_struct;
		(*i)++;
	}
	else
	{
		if (ft_strcmp(arg, "<") == 0 || ft_strcmp(arg, "<<") == 0
			|| ft_strcmp(arg, ">") == 0 || ft_strcmp(arg, ">>") == 0)
			handle_redirections(new_cmd, arg, saveptr2);
		else
		{
			new_cmd->args[*i] = *arg_struct;
			new_cmd->args[*i].ignore_pipe = arg_struct->which_quotes != '\0'
				&& ft_strchr(arg, '|');
			(*i)++;
		}
	}
	arg_struct->which_quotes = '\0';
}

void	parse_arguments(t_command *new_cmd, char *token)
{
	t_arg	arg_struct;
	char	*saveptr2;
	char	*arg;
	int		i;

	i = 0;
	arg_struct.is_first = true;
	arg = ft_strtok_r(token, " ", &saveptr2, &arg_struct);
	arg_struct.is_first = false;
	while (arg != NULL)
	{
		process_argument(new_cmd, &arg_struct, &saveptr2, &i);
		arg = ft_strtok_r(NULL, " ", &saveptr2, &arg_struct);
	}
	new_cmd->args[i].arg = NULL;
}
