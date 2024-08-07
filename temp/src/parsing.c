#include "minishell.h"

size_t	ft_strcspn(const char *str, const char *delim) //znajduje pierwsze wystąpienie znaku z delim w str
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

size_t	ft_strspn(const char *str, const char *delim) //oblicza dlugosc str skladajaca sie tylko z delim
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
    char quote;
    char *start;
    char *end;

	if ((str[0] == '"' && str[1] == '"') || (str[0] == '\'' && str[1] == '\''))
	{
		*in_quotes = true;
		*saveptr = str + 2;
		return (" ");
	}
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


//////////////////////

bool check_pipe_in_quotes(const char *str) {
    bool single_quote_open = false;
    bool double_quote_open = false;

    while (*str) {
        if (*str == '\'' && !double_quote_open) {
            single_quote_open = !single_quote_open;
        } else if (*str == '"' && !single_quote_open) {
            double_quote_open = !double_quote_open;
        } else if (*str == '|' && (single_quote_open || double_quote_open)) {
            return true;
        }
        str++;
    }

    return false;
}
///////////////////////////////////////////////////



char	*ft_strtok_r(char *str, const char *delim, char **saveptr, bool *in_quotes)
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
		return (handle_quotes(str, saveptr, in_quotes));
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
	*in_quotes = false;
	return (start);
}

t_command	*parse_command(char *input)
{
	t_command	*head;
	t_command	*current;
	t_command	*new_cmd;
	char		*token;
	char		*saveptr1;
	bool	in_quotes;

	in_quotes = false;
	head = NULL;
	current = NULL;
	token = ft_strtok_r(input, "|", &saveptr1, &in_quotes);
	while (token != NULL)
	{
		//printf("Parsing token: %s\n", token);
		new_cmd = create_new_command(token);
		if (!new_cmd)
			return (NULL);
		parse_arguments(new_cmd, token);
		add_command_to_list(&head, &current, new_cmd);
		token = ft_strtok_r(NULL, "|", &saveptr1, &in_quotes);
	}
	return (head);
}
