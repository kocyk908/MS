#include "minishell.h"

void	ft_env_val_vol3(char *env, char *trimmed_env, int fd)
{
	int		i;
	int		len_env;
	char	*temp;

	i = 0;
	len_env = ft_strlen_env(env, '=');
	temp = malloc(sizeof(char) * (len_env + 1));
	while (env[i] != '=')
	{
		temp[i] = env[i];
		i++;
	}
	temp[i] = '\0';
	if (!ft_strcmp(trimmed_env, temp))
	{
		ft_putstr_fd(ft_strrchr(env, '=') + 1, fd);
		free(temp);
		return ;
	}
	free(temp);
}

void	ft_env_val_vol2(t_gen *gen, char *trimmed_env, int fd, int i)
{
	while (gen->envs[i])
	{
		if (ft_strchr(gen->envs[i], '='))
			ft_env_val_vol3(gen->envs[i], trimmed_env, fd);
		i++;
	}
}

void	ft_env_val(t_gen *gen, char *str, int fd)
{
	char	*trimmed_env;
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
		ft_putnbr_fd(gen->exit_status, fd);
	i = 0;
	ft_env_val_vol2(gen, trimmed_env, fd, i);
	free(trimmed_env);
}
