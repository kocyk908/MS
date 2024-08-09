#include "minishell.h"

char	*ft_path_cmp(t_gen *gen, char **arr, char *cmd_mod)
{
	char	*temp;
	int		counter;

	counter = 0;
	gen->is_path = 0;
	temp = NULL;
	while (arr[counter])
	{
		temp = ft_strjoin(arr[counter], cmd_mod);
		if (access(temp, X_OK) == 0)
		{
			gen->is_path = 1;
			break ;
		}
		free(temp);
		temp = NULL;
		counter++;
	}
	return (temp);
}

char	*find_path_vol2(t_gen *gen, char *cmd_mod)
{
	char	*valid_path;
	char	*var_path;
	char	**arr;
	int		i;

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
	return (valid_path);
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
	return (valid_path);
}
