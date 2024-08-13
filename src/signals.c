#include "minishell.h"

void	signal_quit_duo(int sig)
{
	(void)sig;
	printf("Quit\n");
}

void	signal_c_duo(int sig)
{
	(void)sig;
	printf("\n");
}

void	signal_c(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_quit(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
	write(STDERR_FILENO, "  \b\b", 4);
}

void	signal_d(void)
{
	printf("exit\n");
	exit(0);
}
