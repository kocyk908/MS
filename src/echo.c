#include "minishell.h"

void	ft_buildin_echo_vol3(t_gen *gen, char **args, int fd, int i)
{
	while (args[i])
	{
		if (args[i][0] == '$')
			ft_env_val(gen, args[i], fd);
		else
			ft_putstr_fd(args[i], fd);
		if (args[i + 1])
			ft_putstr_fd(" ", fd);
		i++;
	}
}

void	ft_buildin_echo_vol2(char **args, int *i, bool *n)
{
	int	j;

	while (args[*i] && args[*i][0] == '-')
	{
		j = 1;
		while (args[*i][j] == 'n')
			j++;
		if (args[*i][j] == '\0')
		{
			*n = true;
			i++;
		}
		else
			break ;
	}
}

void	builtin_echo(char **args, t_redirs *redirs, t_gen *gen)
{
	int		i;
	int		fd;
	bool	n;

	fd = STDOUT_FILENO;
	i = 1;
	n = false;
	ft_buildin_echo_vol2(args, &i, &n);
	if (redirs->is_append || redirs->output_redir != -1)
		fd = redirs->output_redir;
	ft_buildin_echo_vol3(gen, args, fd, i);
	if (!n || redirs->is_append)
		ft_putstr_fd("\n", fd);
}
