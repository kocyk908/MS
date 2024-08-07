#include "minishell.h"

bool	ft_env_cmp(t_gen *gen, char *env)
{
	bool	match;
	int		i;

	match = false;
	i = 0;
	while (gen->envs[i])
	{
		if (ft_strncmp(gen->envs[i], env, ft_strlen_env(gen->envs[i],
					'=')) == 0)
			match = true;
		i++;
	}
	return (match);
}

char	**ft_unset_env_vol2(t_gen *gen, char *env, int env_len)
{
	char	**temp;
	char	*env_to_del;
	int		i;
	int		j;

	temp = malloc(sizeof(char *) * (env_len + 1));
	i = 0;
	j = 0;
	while (gen->envs[i])
	{
		env_to_del = ft_strnstr(gen->envs[i], env, ft_strlen_env(env, '='));
		if (!env_to_del)
		{
			temp[j] = ft_strdup(gen->envs[i]);
			free(gen->envs[i]);
			j++;
		}
		else
			free(gen->envs[i]);
		i++;
	}
	temp[j] = NULL;
	return (temp);
}

void	ft_unset_env(t_gen *gen, char *env)
{
	char	**temp;
	int		env_len;

	env_len = 0;
	while (gen->envs[env_len] != NULL)
		env_len++;
	if (!ft_env_cmp(gen, env))
		return ;
	temp = ft_unset_env_vol2(gen, env, env_len);
	free(gen->envs);
	gen->envs = malloc(sizeof(char *) * (env_len + 1));
	ft_copy_arr(gen->envs, temp, env_len - 1);
	gen->envs[env_len - 1] = NULL;
	ft_free_arr(temp);
}

void	ft_export_env(t_gen *gen, char *env)
{
	char	**temp;
	int		env_len;

	env_len = 0;
	while (gen->envs[env_len] != NULL)
		env_len++;
	if (!ft_strchr(env, '='))
		return ;
	if (ft_env_cmp(gen, env))
	{
		ft_unset_env(gen, env);
		env_len--;
	}
	temp = malloc(sizeof(char *) * (env_len + 2));
	ft_copy_arr(temp, gen->envs, env_len);
	temp[env_len] = ft_strdup(env);
	temp[env_len + 1] = NULL;
	ft_free_arr(gen->envs);
	gen->envs = malloc(sizeof(char *) * (env_len + 2));
	ft_copy_arr(gen->envs, temp, env_len + 1);
	gen->envs[env_len + 1] = NULL;
	ft_free_arr(temp);
}

void	ft_copy_envp(t_gen *gen, char **envp)
{
	int	env_len;

	env_len = 0;
	while (envp[env_len])
		env_len++;
	gen->envs = malloc(sizeof(char *) * (env_len + 1));
	env_len = 0;
	while (envp[env_len])
	{
		gen->envs[env_len] = ft_strdup(envp[env_len]);
		env_len++;
	}
	gen->envs[env_len] = NULL;
}
