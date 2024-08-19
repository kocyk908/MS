/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:02:12 by lkoc              #+#    #+#             */
/*   Updated: 2024/08/20 00:01:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_process_dollar(t_gen *gen, t_arg *arg, int fd, int j)
{
	if (arg->arg[j + 1] == '\0' || arg->arg[j + 1] == ' ')
	{
		ft_putchar_fd('$', fd);
		j++;
	}
	else
	{
		ft_env_val(gen, arg->arg + j, fd, arg->which_quotes);
		while (arg->arg[j] && arg->arg[j] != ' ')
			j++;
	}
	return (j);
}

static int	quote_inside(char *str)
{
	int		i;
	char	quote;
	int		open_quotes;

	i = 0;
	open_quotes = 0;
	quote = '\0';
	while (str[i])
	{
		if (quote == '\0' && (str[i] == '\'' || str[i] == '"'))
		{
			quote = str[i];
			open_quotes++;
		}
		else if (str[i] == quote)
		{
			quote = '\0';
			open_quotes++;
		}
		i++;
	}
	return (open_quotes % 2 == 0);
}

void	ft_buildin_echo_vol3(t_gen *gen, t_arg *args, int fd, int i)
{
	int		j;

	while (args[i].arg)
	{
		j = 0;
		while (args[i].arg[j])
		{
			if (args[i].arg[j] == '$' && args[i].which_quotes != '\'')
				j = ft_process_dollar(gen, &args[i], fd, j);
			else
			{
				if (quote_inside(args[i].arg))
				{
					if (args[i].arg[j] != '\'' && args[i].arg[j] != '"')
						ft_putchar_fd(args[i].arg[j], fd);
				}
				else
					ft_putchar_fd(args[i].arg[j], fd);
				j++;
			}
		}
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
			(*i)++;
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
