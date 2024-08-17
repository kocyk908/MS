/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:02:12 by pruszkie          #+#    #+#             */
/*   Updated: 2024/08/13 23:24:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_quotes(char *str, char **saveptr, char *in_quotes)
{
	char	quote;
	char	*start;
	char	*end;

	quote = str[0];
	start = str + 1;
	end = ft_strchr(start, quote);
	*in_quotes = quote;
	if (end)
	{
		*end = '\0';
		*saveptr = end + 1;
	}
	else
		*saveptr = str + strlen(str);
	return (start);
}

char	*find_next_token(char *str, const char *delim,
				char **saveptr, t_arg *arg_struct)
{
	char	*start;
	bool	inside_quotes;

	start = str;
	inside_quotes = false;
	while (*str)
	{
		if ((*str == '"' || *str == '\'') && !inside_quotes)
			inside_quotes = true;
		else if ((*str == '"' || *str == '\'') && inside_quotes)
			inside_quotes = false;
		else if (ft_strchr(delim, *str) && !inside_quotes)
			break ;
		str++;
	}
	if (*str)
	{
		*str = '\0';
		*saveptr = str + 1;
	}
	else
		*saveptr = str;
	arg_struct->arg = start;
	return (arg_struct->arg);
}

char	*ft_strtok_r(char *str, const char *delim, char **saveptr,
		t_arg *arg_str)
{
	if (!str)
		str = *saveptr;
	if (arg_str->is_first && (str[0] == '\'' || str[0] == '"'))
		str = add_space_at_start(str);
	while (*str && ft_strchr(delim, *str))
		str++;
	if (*str == '\0')
	{
		*saveptr = str;
		return (NULL);
	}
	if (*str == '"' || *str == '\'')
	{
		arg_str->arg = handle_quotes(str, saveptr, &arg_str->which_quotes);
		return (arg_str->arg);
	}
	return (find_next_token(str, delim, saveptr, arg_str));
}
