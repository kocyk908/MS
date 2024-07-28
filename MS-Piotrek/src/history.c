#include "minishell.h"

void ft_history_list(t_gen *gen, char *input)
{
    t_history *new_node;
    t_history *current;
    // gen->history = NULL; // if norm gonna cry move this line
    new_node = malloc(sizeof(t_history)); // free every t_history
    new_node->input = ft_strdup(input); // free every input
    new_node->next = NULL;
    if (gen->history == NULL)
    {
        new_node->num = 1;
        gen->history = new_node;
    }
    else
    {
        current = gen->history;
        while(current->next != NULL)
            current = current->next;
		if(!ft_strcmp(current->input, input))  // why ft_strcmp is working upside down?
		{
			free(new_node->input);
			free(new_node);
			return;
		}
        new_node->num = current->num + 1;
        current->next = new_node;
    }
}

void ft_display_history_list(t_gen *gen)
{
	t_history *temp;
	temp = gen->history;
	int i;

	i = 0;
	while(temp != NULL)
	{
		printf("%d  %s\n",temp->num, temp->input);
		temp = temp->next;
	}
}