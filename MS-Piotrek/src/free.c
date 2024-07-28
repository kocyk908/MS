#include "minishell.h" 

void ft_free_arr(char **arr)
{
	int i;

	i = 0;
	while(arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

void ft_free_path(t_command *command)
{
	while(command != NULL)
	{
		free(command->path);
		command->path = NULL;
		command = command->next;
	}
}

// void ft_free_history(t_history *node)
// {
// 	t_history *prev;

// 		printf("to free, %s\n", node->input);

// 	while(node)
// 	{
// 		prev = node;
// 		node = node->next;
// 		free(prev);
// 		free(prev->input);
// 		prev = NULL;
// 	}
// }