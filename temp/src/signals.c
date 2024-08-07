#include "minishell.h"

void	signal_c(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_d(void)
{
	printf("exit\n");
	exit(0);
}

void	init_signals(void)
{
	signal(SIGINT, signal_c);
	signal(SIGQUIT, SIG_IGN);
}
