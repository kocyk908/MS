#include "minishell.h"

size_t	ft_strcspn(const char *str, const char *delim)
{
	const char	*s;
	const char	*d;

	s = str;
	while (*s)
	{
		d = delim;
		while (*d)
		{
			if (*s == *d)
				return (s - str);
			d++;
		}
		s++;
	}
	return (s - str);
}

size_t	ft_strspn(const char *str, const char *delim)
{
	const char	*s;
	const char	*d;

	s = str;
	while (*s)
	{
		d = delim;
		while (*d)
		{
			if (*s == *d)
				break ;
			d++;
		}
		if (*d == '\0')
			break ;
		s++;
	}
	return (s - str);
}

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

char	*parse_first_quoted_argument(char *str, char **saveptr,
		t_arg *arg_struct)
{
	char	quote;
	char	*start;
	char	*end;

	quote = str[0];
	start = str + 1;
	end = ft_strchr(start, quote);
	if (str[0] == '\'')
		arg_struct->in_quotes = true;
	if (end)
	{
		*end = '\0';
		*saveptr = end + 1;
	}
	else
	{
		*saveptr = str + strlen(str);
	}
	arg_struct->arg = start;
	return (str);
}

char	*add_space_at_start(char *input)
{
	char	*result;

	result = malloc(ft_strlen(input) + 2);
	if (!result)
		return (NULL);
	result[0] = ' ';
	ft_strcpy(result + 1, input);
	return (result);
}

char	*ft_strtok_r(char *str, const char *delim, char **saveptr,
		t_arg *arg_struct)
{
	char	*start;
	bool	inside_quotes;

	inside_quotes = false;
	if (!str)
		str = *saveptr;
	if (arg_struct->is_first && (str[0] == '\'' || str[0] == '"'))
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
		arg_struct->arg = handle_quotes(str, saveptr, &arg_struct->in_quotes);
		return (arg_struct->arg);
	}
	start = str;
	while (*str)
	{
		if ((*str == '"' || *str == '\'') && !inside_quotes)
		{
			inside_quotes = true;
		}
		else if ((*str == '"' || *str == '\'') && inside_quotes)
		{
			inside_quotes = false;
		}
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
	return (start);
}

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

t_command	*parse_command(char *input)
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
	return (head);
}
