/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 01:42:50 by marvin            #+#    #+#             */
/*   Updated: 2024/09/08 01:42:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_dollar_check_vol2(t_gen *gen, char *token)
{
	int		i;
	int		env_len;
	char	*temp;

	i = 0;
	while (gen->envs[i])
	{
		env_len = 0;
		while (gen->envs[i][env_len] != '=')
			env_len++;
		if (ft_strncmp(gen->envs[i], token, env_len) == 0)
			return (gen->envs[i] + env_len + 1);
		i++;
	}
	return ("");
}

static void	ft_shift_arguments_left(char *env, t_arg *args, int start_index)
{
	int	j;

	j = start_index;
	while (args[j].arg)
	{
		args[j].arg = args[j + 1].arg;
		j++;
	}
}

static void	handle_dollar_case(t_gen *gen, t_command *head, int *i)
{
	char	*env;

	if (head->args[*i].arg[1] == '?')
		env = semi_itoa(gen->exit_status);
	else if (ft_strcmp(head->args[*i].arg, "$PWD") == 0)
		env = ft_strdup(getenv("PWD"));
	else
		env = ft_dollar_check_vol2(gen, head->args[*i].arg + 1);
	if (*env == '\0')
		ft_shift_arguments_left(env, head->args, (*i)--);
	else
		head->args[*i].arg = env;
}

void	ft_dollar_check(t_gen *gen, t_command *head)
{
	int		i;
	char	*env;

	i = 0;
	while (head->args[i].arg)
	{
		if (ft_strcmp(head->args[i].arg, "echo") == 0
			|| head->args[i].which_quotes == '\'')
		{
			i += 2;
			continue ;
		}
		if (ft_strcmp(head->args[i].arg, "$") == 0)
			gen->exit_status = 127;
		if (head->args[i].arg[0] == '$')
			handle_dollar_case(gen, head, &i);
		i++;
	}
}
