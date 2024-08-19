/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:02:12 by lkoc              #+#    #+#             */
/*   Updated: 2024/08/18 01:07:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_too_many(int i)
{
	if (i > 2)
	{
		printf("cd: too many arguments\n");
	}
}

int	quote_inside(char *str)
{
	int		i;
	char	quote;
	int		open_quotes;

	i = 0;
	open_quotes = 0;
	quote = '\0';
	while (str[i])
	{
		if (quote == '\0' && (str[i] == '\'' || str[i] == '"'))
		{
			quote = str[i];
			open_quotes++;
		}
		else if (str[i] == quote)
		{
			quote = '\0';
			open_quotes++;
		}
		i++;
	}
	return (open_quotes % 2 == 0);
}

void	remove_enclosing_quotes(char *str)
{
	size_t	len;

	if (!str)
		return ;
	len = ft_strlen(str);
	if (len >= 2 && ((str[0] == '"' && str[len - 1] == '"')
			|| (str[0] == '\'' && str[len - 1] == '\'')))
	{
		ft_memmove(str, str + 1, len - 2);
		str[len - 2] = '\0';
	}
}
//used for exit
