/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:02:12 by pruszkie          #+#    #+#             */
/*   Updated: 2024/08/13 23:26:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_history_list(t_gen *gen, char *input)
{
	t_history	*new_node;
	t_history	*current;

	new_node = malloc(sizeof(t_history));
	new_node->input = ft_strdup(input);
	new_node->next = NULL;
	if (gen->history == NULL)
	{
		new_node->num = 1;
		gen->history = new_node;
	}
	else
	{
		current = gen->history;
		while (current->next != NULL)
			current = current->next;
		if (!ft_strcmp(current->input, input))
		{
			free(new_node->input);
			free(new_node);
			return ;
		}
		new_node->num = current->num + 1;
		current->next = new_node;
	}
}

void	ft_display_history_list(t_gen *gen)
{
	t_history	*temp;

	temp = gen->history;
	while (temp != NULL)
	{
		printf("%d  %s\n", temp->num, temp->input);
		temp = temp->next;
	}
}
