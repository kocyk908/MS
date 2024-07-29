#include "minishell.h"

void ft_unset_env(t_gen *gen, char *env)
{
	char **temp;
	char *env_to_del;
	int env_len;
	int i;
	int j;

	env_len = 0;
	while(gen->envs[env_len] != NULL)
		env_len++;
	temp = malloc(sizeof(char *) * env_len);
	i = 0;
	j = 0;
	while(gen->envs[i])
	{
		env_to_del = ft_strnstr(gen->envs[i], env, ft_strlen(env));
		if(!env_to_del)
		{
			temp[j] = ft_strdup(gen->envs[i]);
			free(gen->envs[i]);

			j++;
			// printf("KEPP THIS: %s\n", gen->envs[i]);
		}
		else
		{
			// printf("-----------DELETE THIS: %s\n", gen->envs[i]);
			free(gen->envs[i]);
		}
		i++;
	}
	temp[j] = NULL;
	free(gen->envs);
	gen->envs = malloc(sizeof(char *) * (env_len + 1));
	ft_copy_arr(gen->envs, temp, env_len - 1);
	gen->envs[env_len - 1] = NULL;
	ft_free_arr(temp);
}

void ft_export_env(t_gen *gen, char *env)
{
	char **temp;
	int env_len;

	env_len = 0;
	while(gen->envs[env_len] != NULL)
		env_len++;
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