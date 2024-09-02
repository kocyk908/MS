/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piotr <piotr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:02:12 by pruszkie          #+#    #+#             */
/*   Updated: 2024/08/31 19:11:47 by piotr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_command_token(char *token, t_command **head, t_command **current)
{
	t_command	*new_cmd;
	new_cmd = create_new_command(token);
	if (!new_cmd)
		return (0);
	parse_arguments(new_cmd, token);
	add_command_to_list(head, current, new_cmd);
	return (1);
}

void ft_dollar_check(t_command *head)
{
	int i;

	i = 0;
	while(head->args[i].arg)
	{
		if(head->args[i].arg[0] == '$')
			printf("arg: %c\n", head->args[i].arg[0]);
		i++;
	}
}

t_command	*parse_command(char *input)
{
	t_command	*head;
	t_command	*current;
	t_arg		arg_struct;
	char		*token;
	char		*saveptr1;

	head = NULL;
	current = NULL;
	token = ft_strtok_r(input, "|", &saveptr1, &arg_struct);
	while (token != NULL)
	{
		if (!process_command_token(token, &head, &current))
			return (NULL);
		token = ft_strtok_r(NULL, "|", &saveptr1, &arg_struct);
	}
	ft_dollar_check(head);
	return (head);
}
