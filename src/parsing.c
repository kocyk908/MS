/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkoc <lkoc@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:02:12 by pruszkie          #+#    #+#             */
/*   Updated: 2024/09/05 18:11:11 by lkoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_command_token(char *token, t_command **head, t_command **current)
{
	t_command	*new_cmd;

	new_cmd = create_new_command(token);
	if (!new_cmd)
		return (0);
	parse_arguments(new_cmd, token);
	add_command_to_list(head, current, new_cmd);
	return (1);
}

// bool ft_is_numeric(char *str)
// {
//     if (str == NULL || *str == '\0') 
//         return false;
//     if (*str == '-' || *str == '+') 
//         str++;
// 	while(*str)
// 	{
// 		if(!ft_isdigit(*str))
// 			return false;
// 		str++;
// 	}
// 	return true;
// }

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
			i = i + 2;
			continue ;
		}
		if (head->args[i].arg[0] == '$')
		{
			env = ft_dollar_check_vol2(gen, head->args[i].arg + 1);
			if (head->args[i].arg[1] == '?')
				env = ft_itoa(gen->exit_status);
			head->args[i].arg = env;
		}
		i++;
	}
}

t_command	*parse_command(t_gen *gen, char *input)
{
	t_command	*head;
	t_command	*current;
	t_arg		arg_struct;
	char		*token;
	char		*saveptr1;

	head = NULL;
	current = NULL;
	token = ft_strtok_r(input, "|", &saveptr1, &arg_struct);
	while (token != NULL)
	{
		if (!process_command_token(token, &head, &current))
			return (NULL);
		token = ft_strtok_r(NULL, "|", &saveptr1, &arg_struct);
	}
	ft_dollar_check(gen, head);
	return (head);
}
