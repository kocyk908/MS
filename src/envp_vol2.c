/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_vol2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:02:12 by pruszkie          #+#    #+#             */
/*   Updated: 2024/08/20 00:15:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_env_val(t_gen *gen, char *str, int fd, char quotes)
{
	char	*trimmed_env;
	int		i;

	trimmed_env = malloc(sizeof(char) * ft_strlen(str));
	i = 0;
	while (str[i + 1])
	{
		if (str[i + 1] == ' ' && quotes == '"')
			break ;
		trimmed_env[i] = str[i + 1];
		i++;
	}
	trimmed_env[i] = '\0';
	if (trimmed_env[0] == '?')
	{
		ft_putnbr_fd(gen->exit_status, fd);
		if (!(trimmed_env[1] >= 9 && trimmed_env[1] <= 13)
			&& trimmed_env[1] != ' ' && trimmed_env[1] != '\0')
			ft_putstr_fd(trimmed_env + 1, 1);
	}
	i = 0;
	ft_env_val_vol2(gen, trimmed_env, fd, i);
	free(trimmed_env);
}
