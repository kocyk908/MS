/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_in_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 01:44:41 by marvin            #+#    #+#             */
/*   Updated: 2024/09/08 01:44:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	variable_set(int *i, int *j, int *inside_quotes)
{
	*i = 0;
	*j = 0;
	*inside_quotes = 0;
}

char	*ft_remove_outer_quotes(char *str)
{
	int		i;
	int		j;
	int		inside_quotes;
	char	*new_str;

	new_str = malloc(ft_strlen(str) + 1);
	if (!new_str)
		return (NULL);
	variable_set(&i, &j, &inside_quotes);
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			if (inside_quotes == 0)
				inside_quotes = 1;
			else
				inside_quotes = 0;
		}
		else
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}
