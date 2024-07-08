#include "minishell.h"

char	*concat_path(const char *dir, const char *cmd)
{
	size_t	dir_len;
	size_t	cmd_len;
	char	*full_path;

	dir_len = ft_strlen(dir);
	cmd_len = ft_strlen(cmd);
	full_path = malloc(dir_len + cmd_len + 2);	// 1 na '/' i 1 na '\0'
	if (!full_path)
        	return (NULL);
	ft_strcpy(full_path, dir);
	ft_strcat(full_path, "/");				// dodaje "/" na końcu full_path
	ft_strcat(full_path, cmd);				// dodaje cmd na końcu full_path
	return (full_path);
}

char	*find_path(char *cmd, char **envp)
{
	char	*path;
	char	*paths;
	char	*token;
	char	*full_path;

	path = getenv("PATH");
	if (!path)
		return (NULL);
	paths = ft_strdup(path);
	token = ft_strtok_r(paths, ":",);
	while (token)
	{
		full_path = concat_path(token, cmd);
		if (access(full_path, X_OK) == 0)		// sprawdza dostęp do pliku
		{
			free(paths);
			return (full_path);
		}
		free(full_path);
		token = ft_strtok_r(NULL, ":");
	}
	free(paths);
	return (NULL);
}
