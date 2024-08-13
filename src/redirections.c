#include "minishell.h"
#include <errno.h>

void	handle_input_redir(t_redirs *redirs, char **saveptr2)
{
	char	*arg;
	t_arg	token;

	token.in_quotes = false;
	arg = ft_strtok_r(NULL, " ", saveptr2, &token);
	redirs->input_redir = open(arg, O_RDONLY);
	if (redirs->input_redir == -1)
		perror("open input redir");
}

void	handle_output_redir(t_redirs *redirs, char **saveptr2)
{
	char	*arg;
	int		fd;
	t_arg	token;

	token.in_quotes = false;
	arg = ft_strtok_r(NULL, " ", saveptr2, &token);
	fd = open(arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open output redir");
		return ;
	}
	redirs->output_redir = fd;
}

void	handle_append_redir(t_redirs *redirs, char **saveptr2)
{
	char	*arg;
	int		fd;
	t_arg	token;

	token.in_quotes = false;
	arg = ft_strtok_r(NULL, " ", saveptr2, &token);
	fd = open(arg, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		fd = open(arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror("open append redir");
			return ;
		}
	}
	redirs->output_redir = fd;
	redirs->is_append = 1;
}
