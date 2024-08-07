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

char	*handle_quotes(char *str, char **saveptr)
{
	char	quote;
	char	*start;
	char	*end;

	quote = str[0];
	start = str + 1;
	end = ft_strchr(start, quote);
	if (end)
	{
		*end = '\0';
		*saveptr = end + 1;
	}
	else
		*saveptr = str + ft_strlen(str);
	return (start);
}

char	*ft_strtok_r(char *str, const char *delim, char **saveptr)
{
	char	*start;

	if (!str)
		str = *saveptr;
	while (*str && ft_strchr(delim, *str))
		str++;
	if (*str == '\0')
	{
		*saveptr = str;
		return (NULL);
	}
	if (*str == '"' || *str == '\'')
		return (handle_quotes(str, saveptr));
	start = str;
	while (*str && !ft_strchr(delim, *str))
		str++;
	if (*str)
	{
		*str = '\0';
		*saveptr = str + 1;
	}
	else
		*saveptr = str;
	return (start);
}

t_command	*parse_command(char *input)
{
	t_command	*head;
	t_command	*current;
	t_command	*new_cmd;
	char		*token;
	char		*saveptr1;

	head = NULL;
	current = NULL;
	token = ft_strtok_r(input, "|", &saveptr1);
	while (token != NULL)
	{
		new_cmd = create_new_command(token);
		if (!new_cmd)
			return (NULL);
		parse_arguments(new_cmd, token);
		add_command_to_list(&head, &current, new_cmd);
		token = ft_strtok_r(NULL, "|", &saveptr1);
	}
	return (head);
}
