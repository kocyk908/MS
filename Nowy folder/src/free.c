/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piotr <piotr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:02:12 by lkoc              #+#    #+#             */
/*   Updated: 2024/09/03 17:36:37 by piotr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	ft_free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

void	ft_free_path(t_command *command)
{
	while (command != NULL)
	{
		free(command->path);
		command->path = NULL;
		command = command->next;
	}
}

void	ft_free_pipes(t_gen *gen)
{
	int	i;

	i = 0;
	while (i < (gen->num_of_cmds - 1))
	{
		free(gen->pipes[i]);
		i++;
	}
	free(gen->pipes);
}

void	ft_free_history(t_history *node)
{
	t_history	*prev;

	while (node)
	{
		prev = node;
		node = node->next;
		free(prev->input);
		free(prev);
		prev = NULL;
	}
}
