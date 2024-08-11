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

int	digits_only(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (i != 0 && str[i] == '-')
			return (0);
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	ft_copy_arr(char **dest, char **src, int arr_len)
{
	int	i;

	i = 0;
	while (i < arr_len)
	{
		dest[i] = ft_strdup(src[i]);
		i++;
	}
}

int	ft_strlen_env(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c && str[i] != '\0')
		i++;
	return (i);
}


void	wypisanko(char *token, char *input)
{
	write(1, "\nszukane -> ", 12);
	ft_putstr_fd(input, 1);
	puts(token);
	write(1, "\n", 1);
}