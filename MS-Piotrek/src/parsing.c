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

char	*ft_strtok_r(char *str, const char *delim, char **saveptr)	// Dzieli delimiterem zdanie 
{
	char	*end;

	if (!str)
		str = *saveptr;
	if (*str == '\0')
	{
		*saveptr = str;
		return (NULL);
	}
	str += ft_strspn(str, delim);
	if (*str == '\0')
	{
		*saveptr = str;
		return (NULL);
	}
	end = str + ft_strcspn(str, delim);
	if (*end == '\0')
	{
		*saveptr = end;
		return (str);
	}
	*end = '\0';
	*saveptr = end + 1;
	return (str);
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

/*
t_command	*parse_command(char *input)
{
	t_command	*head;
	t_command	*current;
	t_command	*new_cmd;
	char		*token;
	char		*saveptr1;
	char		*saveptr2;
	char		*arg;
	int			i;

	head = NULL;
	current = NULL;
	// Tokenizacja komendy po znakach pipe'ów
	token = ft_strtok_r(input, "|", &saveptr1);
	while (token != NULL)
	{
		new_cmd = malloc(sizeof(t_command));
		if (!new_cmd)
			return (0); //exit(EXIT_FAILURE);
		new_cmd->args = malloc(64 * sizeof(char *)); // Maksymalna liczba argumentów = 64 do zmiany chyba
		if (!new_cmd->args)
			return (0); //exit(EXIT_FAILURE);
		new_cmd->redirs.input_redir = -1;
		new_cmd->redirs.output_redir = -1;
		new_cmd->redirs.is_append = 0;
		new_cmd->redirs.is_heredoc = 0;
		new_cmd->next = NULL;
		// Tokenizacja argumentów
		i = 0;
		arg = ft_strtok_r(token, " ", &saveptr2);
		while (arg != NULL)
		{
			if (strcmp(arg, "<") == 0)
			{
				arg = ft_strtok_r(NULL, " ", &saveptr2);
				new_cmd->redirs.input_redir = open(arg, O_RDONLY);
				if (new_cmd->redirs.input_redir == -1)
					return (0); //exit(EXIT_FAILURE);
			}
			else if (strcmp(arg, "<<") == 0)
			{
				arg = ft_strtok_r(NULL, " ", &saveptr2);
				new_cmd->redirs.is_heredoc = 1;
				// Tu należy obsłużyć heredoc
			}
			else if (strcmp(arg, ">") == 0)
			{
				arg = ft_strtok_r(NULL, " ", &saveptr2);
				new_cmd->redirs.output_redir = open(arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (new_cmd->redirs.output_redir == -1)
					return (0); //exit(EXIT_FAILURE);
			}
			else if (strcmp(arg, ">>") == 0)
			{
				arg = ft_strtok_r(NULL, " ", &saveptr2);
				new_cmd->redirs.output_redir = open(arg, O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (new_cmd->redirs.output_redir == -1)
					return (0); //exit(EXIT_FAILURE);
				new_cmd->redirs.is_append = 1;
			}
			else
			{
				new_cmd->args[i++] = arg;
			}
			arg = ft_strtok_r(NULL, " ", &saveptr2);
		}
		new_cmd->args[i] = NULL;
		if (!head)
		{
			head = new_cmd;
			current = new_cmd;
		}
		else
		{
			current->next = new_cmd;
			current = new_cmd;
		}
		token = ft_strtok_r(NULL, "|", &saveptr1);
	}
	return (head);
}*/
