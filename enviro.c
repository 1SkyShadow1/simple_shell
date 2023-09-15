#include "shell.h"

/**
 *create_shell_environment - creates shell environment
 *@env_vars: Evironment passed to the main
 *
 * Return: pointer to new environment
 */
char **create_shell_environment(char **env_vars)
{
	char **new_env_vars = NULL;
	size_t x;

	for (x = 0; env_vars[x] != NULL; x++)
		;
	new_env_vars = malloc(sizeof(char *) * (x + 1));
	if (new_env_vars == NULL)
	{
		perror("Fatal Error");
		exit(1);
	}
	for (x = 0; env_vars[x] != NULL; x++)
		new_env_vars[x] = duplicate_custom_string(env_vars[x]);
	new_env_vars[x] = NULL;
	return (new_env_vars);
}

/**
 * destroy_shell_environment - free shell
 * @env_vars: shell environment
 *
 */
void destroy_shell_environment(char **env_vars)
{
	unsigned int x;

	x = 0;
	while (env_vars[x] != NULL)
	{
		free(env_vars[x]);
		x++;
	}

	free(env_vars);
}
