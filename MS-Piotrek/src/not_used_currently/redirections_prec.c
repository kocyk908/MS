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
	char	*str;
	char 	*temp;

	temp = NULL;
	arg = ft_strtok_r(NULL, " ", saveptr2);
	redirs->is_heredoc = 1;
	redirs->input_redir = open("heredoc.txt", O_WRONLY | O_CREAT, 0644);
	while(1)
	{
		str = readline(">");
		if(ft_strncmp(str, arg, ft_strlen(arg)) == 0)
		{
			if(temp)
				ft_putstr_fd(temp, redirs->input_redir);
			break;
		}
		else
		{
			if(temp)
			{
				ft_putstr_fd(temp, redirs->input_redir);
				ft_putchar_fd('\n', redirs->input_redir);
			}
			temp = str;
		}
	}
	close(redirs->input_redir);
	redirs->input_redir = open("heredoc.txt", O_RDONLY);
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
