#include "minishell.h"

void	display_prompt(void)
{
	char	*input;

	input = readline("msh> ");
	if (input)
	{
		add_history(input); //działająca historia
	}
	free(input);
}
