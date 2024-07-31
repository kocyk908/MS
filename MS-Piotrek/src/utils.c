#include "minishell.h"

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

void ft_copy_arr(char **dest, char **src, int arr_len)
{
	int i;

	i = 0;
	while(i < arr_len)
    {
		dest[i] = ft_strdup(src[i]);
        i++;
    }
}