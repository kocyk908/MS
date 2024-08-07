#include "minishell.h"

void	ft_env_val_vol2(t_gen *gen, char *trimmed_env, int fd)
{
	int		i;
	int		j;
	int		len_env;
	char	*env;
	char	*gg;

	i = 0;
	while (gen->envs[i])
	{
		if (ft_strchr(gen->envs[i], '='))
		{
			j = 0;
			len_env = ft_strlen_env(gen->envs[i], '=');
			env = malloc(sizeof(char) * (len_env + 1));
			while (gen->envs[i][j] != '=')
			{
				env[j] = gen->envs[i][j];
				j++;
			}
			env[j] = '\0';
			if (!ft_strcmp(trimmed_env, env))
			{
				ft_putstr_fd(ft_strrchr(gen->envs[i], '=') + 1, fd);
				free(env);
				return ;
			}
			free(env);
		}
		i++;
	}
}

void	ft_env_val(t_gen *gen, char *str, int fd)
{
	char	*trimmed_env;
	int		len_env;
	int		i;

	trimmed_env = malloc(sizeof(char) * ft_strlen(str));
	i = 0;
	while (str[i + 1])
	{
		trimmed_env[i] = str[i + 1];
		i++;
	}
	trimmed_env[i] = '\0';
	if (!ft_strcmp(trimmed_env, "?"))
	{
		ft_putnbr_fd(gen->exit_status, fd);
	}
	ft_env_val_vol2(gen, trimmed_env, fd);
	free(trimmed_env);
}