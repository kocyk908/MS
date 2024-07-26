#include "minishell.h"

void ft_export_env(t_gen *gen, char *env)
{
	char **temp;
	int i;

	temp = gen->envs;
	i = 0;
	while(temp[i] != NULL)
	{
		i++;
		printf("- %s\n", temp[i]);
	}
}

int	is_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "exit") == 0)
		|| (ft_strcmp(cmd, "history") == 0) || (ft_strcmp(cmd, "export") == 0);
}

void	init_structs(t_gen **gen, t_redirs **redirs)
{
	*gen = malloc(sizeof(t_gen));
	*redirs = malloc(sizeof(t_redirs));
	if (!(*gen) || !(*redirs))
	{
		if (*gen)
			free(*gen);
		if (*redirs)
			free(*redirs);
		exit(EXIT_FAILURE);
	}
}

void	process_input(t_gen *gen, t_redirs *redirs, char *input)
{
	t_command	*cmd_list;

	add_history(input);
	ft_history_list(gen, input);

	cmd_list = parse_command(input);

	gen->num_of_cmds = ft_count_cmds(cmd_list);

	if (cmd_list && is_builtin(cmd_list->args[0]))
		execute_builtin(cmd_list, gen);
	else
		execute_pipeline(cmd_list, gen, redirs);
	free_command(cmd_list);
}

int	main(int ac, char **av, char **envp)
{
	char		*input;
	t_gen		*gen;
	t_redirs	*redirs;

	(void)ac;
	(void)av;
	init_structs(&gen, &redirs);
	gen->envs = envp;
	while (1)
	{
		input = readline("msh> ");
		if (input && *input != '\0')
		{
			process_input(gen, redirs, input);
			free(input);
		}
		else
			free(input);
	}
	return (0);
}

// int	main(int ac, char **av, char **envp)
// {
// 	char		*input;
// 	t_gen		*gen;
// 	t_redirs	*redirs;
// 	t_command	*cmd_list;
// 	t_command	*temp;
// 	int			cmd_count;

// 	cmd_count = 0;
// 	(void)ac;
// 	(void)av;
// 	gen = malloc(sizeof(t_gen));
// 	redirs = malloc(sizeof(t_redirs));
// 	if (!gen || !redirs)
// 		return (0);
// 	redirs->input_redir1 = NULL;
// 	while (1)
// 	{
// 		input = readline("msh> ");
// 		if (input)
// 		{
// 			add_history(input);
// 			cmd_list = parse_command(input);
// 			temp = cmd_list;
// 			cmd_count = 0;
// 			while (temp)
// 			{
// 				printf("Command %d: %s\n", cmd_count + 1, temp->args[0]);
// 				cmd_count++;
// 				temp = temp->next;
// 			}
// 			printf("Total number of commands: %d\n", cmd_count);
// 			gen->num_of_cmds = cmd_count;
// 			execute_pipeline(cmd_list, gen, redirs, envp);
// 			free_command(cmd_list);
// 		}
// 		free(input);
// 	}
// 	return (0);
// }

/*

Update 11.07.24

Echo problematyczne gdy argument podany jest w "", jeszcze nie ogarnąłem tego

Update 07.07.24

Udało mi sie już jakoś połączyć procesy w pętlach. 
Póki co to działałem na harkodowanych zmiennych jak path, ilość komend itp
Na tą chwilę potrzeba:

1. Uzupełnić int num_of_cmds w s_gen - długość listy komend. Ja to mogę zrobić.		# w trakcie
2. Uzupełnić char *path w s_command - ścieżka do programu np: "/usr/bin/cat"		
3. Uzupełnić redirsy:
    a) int input_redir - będzie zawirać file descriptor będący wynikiem funckji open
    b) analogicznie output_redir;

Uzupełnienie tego powinno już pozwolić połączyć to wszystko.
Potem zajmiemy sie heredoc i append.

--------------------------------------------------------------------------

Robię tak że execute_pipeline przyjmie następujące informacje
1. input redirection w formie ścieżki pliku w postaci 
    stringa np: "infile.txt"
2. porzebuję ścieżki do każdej komendy znajdującej się command.
    Utworzyłem membere commant->path. Scieżka powinna wyglądać np:
    "/usr/bin/ls" dla programu ls 

*/
