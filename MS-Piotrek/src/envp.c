#include "minishell.h"

void ft_export_env(t_gen *gen, char *env)
{
	char **temp;
	int env_len;
	int i;

	env_len = 0;
	while(gen->envs[env_len] != NULL)
		env_len++;
	temp = malloc(sizeof(char *) * (env_len + 2));
	i = 0;
	while(i < env_len)
    {
		temp[i] = ft_strdup(gen->envs[i]);
        i++;
    }
	temp[i] = ft_strdup(env);
	temp[i + 1] = NULL;
	ft_free_arr(gen->envs);
	gen->envs = malloc(sizeof(char *) * (env_len + 2));
	i = 0;
	while(temp[i])
    {
		gen->envs[i] = ft_strdup(temp[i]);
        i++;
    }
	gen->envs[i] = NULL;
	ft_free_arr(temp);
}

void ft_copy_envp(t_gen *gen, char **envp)
{
	int env_len;

	env_len = 0;
	while(envp[env_len])
		env_len++;
	gen->envs = malloc(sizeof(char *) * (env_len + 1));
	env_len = 0;
	while(envp[env_len])
	{
		gen->envs[env_len] = ft_strdup(envp[env_len]);
		env_len++;
	}
	gen->envs[env_len] = NULL;
}