#include "minishell.h"

void	print_error(char *cmd)
{
	printf("bash: '%s' not found\n", cmd);
	return ;
}

void	ft_freemem(char **arr)
{
	int	j;

	j = 0;
	while (arr[j])
	{
		free(arr[j]);
		j++;
	}
	free(arr);
}

char	*ft_path_cmp(char **arr, char *cmd_mod)
{
	char	*valid_path;
	char	*temp;
	int		counter;

	counter = 0;
	valid_path = NULL;
	while (arr[counter])
	{
		temp = ft_strjoin(arr[counter], cmd_mod);
		if (access(temp, X_OK) == 0)
		{
			valid_path = temp;
			break ;
		}
		free(temp);
		counter++;
	}
	return (valid_path);
}

char	*find_path(char *cmd1, char **envp)
{
	char	*valid_path;
	char	*var_path;
	char	**arr;
	char	*temp;
	char	*cmd_mod;

	valid_path = NULL;
	temp = ft_strdup("/");
	cmd_mod = ft_strjoin(temp, cmd1);
	free(temp);
	while (*envp)
	{
		var_path = ft_strnstr(*envp, "PATH", 4);
		if (var_path)
		{
			arr = ft_split(var_path, ':');
			valid_path = ft_path_cmp(arr, cmd_mod);
			ft_freemem(arr);
		}
		envp++;
	}
	free(cmd_mod);
	if (!valid_path)
		print_error(cmd1);
	return (valid_path);
}
