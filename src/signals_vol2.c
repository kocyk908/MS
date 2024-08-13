#include "minishell.h"

void	init_signals(void)
{
	signal(SIGQUIT, signal_quit);
	signal(SIGINT, signal_c);
}

void	init_signals_duo(void)
{
	signal(SIGQUIT, signal_quit_duo);
	signal(SIGINT, signal_c_duo);
}
