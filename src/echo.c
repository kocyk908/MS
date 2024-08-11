#include "minishell.h"

void	ft_buildin_echo_vol3(t_gen *gen, t_arg *args, int fd, int i)
{
	while (args[i].arg)
	{
		//printf("Arg[%d]: %s, in_quotes: %d\n", i, args[i].arg, args[i].in_quotes);
		if (args[i].arg[0] == '$' && !(args[i].in_quotes))
			ft_env_val(gen, args[i].arg, fd);
		else
			ft_putstr_fd(args[i].arg, fd);
		if (args[i + 1].arg)
			ft_putstr_fd(" ", fd);
		i++;
	}
}

void	ft_buildin_echo_vol2(t_arg *args, int *i, bool *n)
{
	int	j;

	while (args[*i].arg && args[*i].arg[0] == '-')
	{
		j = 1;
		while (args[*i].arg[j] == 'n')
			j++;
		if (args[*i].arg[j] == '\0')
		{
			*n = true;
			i++;
		}
		else
			break ;
	}
}

void	builtin_echo(t_arg *args, t_redirs *redirs, t_gen *gen)
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
