#include "minishell.h"

void	ft_handle_heredoc_vol3(char *temp, int fd)
{
	ft_putstr_fd(temp, fd);
	ft_putchar_fd('\n', fd);
	free(temp);
}

void	ft_handle_heredoc_vol2(char *arg, char *temp, int fd)
{
	char	*str;

	while (1)
	{
		str = readline(">");
		if (ft_strncmp(str, arg, ft_strlen(arg)) == 0)
		{
			if (temp)
				ft_handle_heredoc_vol3(temp, fd);
			free(str);
			break ;
		}
		else
		{
			if (temp)
				ft_handle_heredoc_vol3(temp, fd);
			temp = str;
		}
	}
}

void	handle_heredoc(t_redirs *redirs, char **saveptr2)
{
	char	*arg;
	char	*temp;

	temp = NULL;
	arg = ft_strtok_r(NULL, " ", saveptr2);
	redirs->is_heredoc = 1;
	redirs->input_redir = open("heredoc.txt", O_WRONLY | O_CREAT, 0644);
	ft_handle_heredoc_vol2(arg, temp, redirs->input_redir);
	close(redirs->input_redir);
	redirs->input_redir = open("heredoc.txt", O_RDONLY);
}
