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

char	*handle_quotes(char *str, char **saveptr, bool *in_quotes)
{
	char	quote;
	char	*start;
	char	*end;

	quote = str[0];
	start = str + 1;
	end = ft_strchr(start, quote);
	if (quote == '\'')
		*in_quotes = true;
	else
		*in_quotes = false;
	if (end)
	{
		*end = '\0';
		*saveptr = end + 1;
	}
	else
		*saveptr = str + strlen(str);
	return (start);
}

char	*skip_delimiters(char *str, const char *delim)
{
	while (*str && ft_strchr(delim, *str))
		str++;
	return (str);
}

char	*find_token_end(char *str, const char *delim, bool *inside_quotes)
{
	while (*str)
	{
		if ((*str == '"' || *str == '\''))
			*inside_quotes = !*inside_quotes;
		else if (ft_strchr(delim, *str) && !*inside_quotes)
			break ;
		str++;
	}
	return (str);
}

char	*ft_strtok_r(char *str, const char *delim, char **saveptr, t_arg *arg)
{
	char	*start;

	if (!str)
		str = *saveptr;
	if (arg->is_first && (str[0] == '\'' || str[0] == '"'))
		str = add_space_at_start(str);
	str = skip_delimiters(str, delim);
	if (*str == '\0')
	{
		*saveptr = str;
		return (NULL);
	}
	if (*str == '"' || *str == '\'')
		return (arg->arg = handle_quotes(str, saveptr, &arg->in_quotes));
	start = str;
	str = find_token_end(str, delim, &arg->in_quotes);
	if (*str)
	{
		*str = '\0';
		*saveptr = str + 1;
	}
	else
		*saveptr = str;
	arg->arg = start;
	return (start);
}
