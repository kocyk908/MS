#include "minishell.h"

void	print_error(char *cmd)
{
	printf("bash: '%s' not found\n", cmd);
	return ;
}

// void	ft_freemem(char **arr)
// {
// 	int	j;

// 	j = 0;
// 	while (arr[j])
// 	{
// 		free(arr[j]);
// 		j++;
// 	}
// 	free(arr);
// }

char	*ft_path_cmp(t_gen *gen, char **arr, char *cmd_mod)
{
	char	*temp;
	int		counter;

	counter = 0;
	gen->isPath = 0;
	temp = NULL;
	while (arr[counter])
	{
		temp = ft_strjoin(arr[counter], cmd_mod);
		if (access(temp, X_OK) == 0)
		{
			gen->isPath = 1;
			break ;
		}
		free(temp);
		counter++;
	}
	return (temp);
}

char *find_path_vol2(t_gen *gen, char *cmd_mod)
{
	char	*valid_path;
	char	*var_path;
	char	**arr;

	int i;

	valid_path = NULL;
	i = 0;
	while (gen->envs[i])
	{
		var_path = ft_strnstr(gen->envs[i], "PATH", 4);
		if (var_path)
		{
			arr = ft_split(var_path, ':');
			valid_path = ft_path_cmp(gen, arr, cmd_mod);
			ft_free_arr(arr);
		}
		i++;
	}
	return(valid_path);
}

char	*find_path(char *cmd1, t_gen *gen)
{
	char	*valid_path;
	char	*temp;
	char	*cmd_mod;

	if (access(cmd1, X_OK) == 0)
		return (cmd1);
	valid_path = NULL;
	temp = ft_strdup("/");
	cmd_mod = ft_strjoin(temp, cmd1);
	free(temp);
	
	valid_path = find_path_vol2(gen, cmd_mod);
	free(cmd_mod);
	if (!valid_path)
		print_error(cmd1);
	return (valid_path);
}
