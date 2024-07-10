#include "minishell.h"

void	handle_input_redir(t_redirs *redirs, char **saveptr2)
{
	char	*arg;

	arg = NULL;
	if (saveptr2)
		arg = ft_strtok_r(NULL, " ", saveptr2);
	else
		arg = redirs->input_redir1;
	redirs->input_redir = open(arg, O_RDONLY);
	redirs->input_redir1 = ft_strdup(arg);
	if (redirs->input_redir == -1)
		perror("open input redir");
}

void	handle_heredoc(t_redirs *redirs, char **saveptr2)
{
	char	*arg;

	arg = ft_strtok_r(NULL, " ", saveptr2);
	redirs->is_heredoc = 1;
	// Handle heredoc here
}

void	handle_output_redir(t_redirs *redirs, char **saveptr2)
{
	char	*arg;

	arg = ft_strtok_r(NULL, " ", saveptr2);
	redirs->output_redir = open(arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	redirs->output_redir1 = ft_strdup(arg);
	if (redirs->output_redir == -1)
		perror("open output redir");
}

void	handle_append_redir(t_redirs *redirs, char **saveptr2)
{
	char	*arg;

	arg = ft_strtok_r(NULL, " ", saveptr2);
	redirs->output_redir = open(arg, O_WRONLY | O_CREAT | O_APPEND, 0644);
	redirs->output_redir1 = ft_strdup(arg);
	if (redirs->output_redir == -1)
		perror("open append redir");
	redirs->is_append = 1;
}
