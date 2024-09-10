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

static char	*copy_string(const char *src)
{
	static char	temp[COPY_BUFFER];
	size_t		i;

	i = 0;
	while (src[i] != '\0' && i <= COPY_BUFFER)
	{
		temp[i] = src[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

static void	init_vars_hanquo(char *str, char **start, char **end, char *quote)
{
	*quote = str[0];
	*start = str + 1;
	*end = ft_strchr(*start, *quote);
}

char	*handle_quotes(char *str, char **saveptr, char *in_quotes)
{
	char	*start;
	char	*end;
	char	*combined;
	char	*temp;

	init_vars_hanquo(str, &start, &end, in_quotes);
	if (end)
	{
		*end = '\0';
		*saveptr = end + 1;
		if (**saveptr && !ft_strchr(" \t\n", **saveptr))
		{
			combined = ft_strjoin(start, *saveptr);
			*saveptr += strlen(*saveptr);
			temp = copy_string(combined);
			free(combined);
			return (temp);
		}
		return (start);
	}
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
	while (*str && (!ft_strchr(delim, *str) || inside_quotes))
	{
		if ((*str == '"' || *str == '\''))
			inside_quotes = !inside_quotes;
		str++;
	}
	if (!inside_quotes && *str && !ft_strchr(delim, *str) && *saveptr)
		arg_struct->arg = ft_strjoin(start, *saveptr);
	else
	{
		if (*str)
			*str++ = '\0';
		*saveptr = str;
		arg_struct->arg = start;
	}
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
