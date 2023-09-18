#include "shell.h"

/**
 * identify_shell_builtin - checks if command is builtin
 * @info: shell info structure
 * Return: pointer to function
 */
void (*identify_shell_builtin(shell_info_t *info))(shell_info_t *info)
{
	unsigned int x;
	shell_builtin_t check[] = {
		{"exit", exit_shell},
		{"env", show_shell_environment},
		{"setenv", set_shell_environment},
		{"unsetenv", unset_shell_environment},
		{NULL, NULL}
	};
	x = 0;
	while (check[x].builtin_func != NULL)
	{
		if (compare_custom_strings(info->args[0], check[x].builtin_name) == 0)
			break;
		x++;
	}
	if (check[x].builtin_func != NULL)
		check[x].builtin_func(info);
	return (check[x].builtin_func);

}

/**
 * exit_shell - exits shell
 * @info: shell info
 */
void exit_shell(shell_info_t *info)
{
	int status;

	if (compare_custom_strings(info->args[0], "exit") == 0
			&& info->args[1] != NULL)
	{
		status = convert_string_to_int(info->args[1]);
		if (status == -1)
		{
			info->exit_code = 2;
			print_custom_error(info, ": Illegal number: ");
			print_custom_error_message(info->args[1]);
			print_custom_error_message("\n");
			free(info->cmd_list);
			info->cmd_list = NULL;
			return;
		}
		info->exit_code = status;
	}
	free(info->cmd_buffer);
	free(info->args);
	free(info->cmd_list);
	destroy_shell_environment(info->env_vars);
	exit(info->exit_code);

}

/**
 * show_shell_environment - print shell environment
 * @info: shell info
 */
void show_shell_environment(shell_info_t *info)
{
	unsigned int x;

	x = 0;
	while (info->env_vars[x])
	{
		print_custom_string(info->env_vars[x]);
		print_custom_string("\n");
		x++;
	}
	info->exit_code = 0;
}

/**
 *set_shell_environment - create new environment variable
 *@info: points to shell info
 */

void set_shell_environment(shell_info_t *info)
{
	char **ky;
	char *var;

	if (info->args[1] == NULL || info->args[2] == NULL)
	{
		print_custom_error(info, ": Incorrect number of args\n");
		info->exit_code = 2;
		return;
	}
	ky = find_custom_key(info->env_vars, info->args[1]);
	if (ky == NULL)
	{
		add_custom_key(info);

	}
	else
	{
		var = add_custom_value(info->args[1], info->args[2]);
		if (var == NULL)
		{
			print_custom_error(info, NULL);
			free(info->cmd_buffer);
			free(info->cmd_list);
			free(info->args);
			destroy_shell_environment(info->env_vars);
			exit(127);

		}
		free(*ky);
		*ky = var;
	}
	info->exit_code = 0;
}

/**
 *unset_shell_environment - removes env variable
 *@info: pointer to shell
 */
void unset_shell_environment(shell_info_t *info)
{
	char **ky, **newenv;

	unsigned int x, y;

	if (info->args[1] == NULL)
	{

		print_custom_error(info, ": Incorrect number of args\n");
		info->exit_code = 2;
		return;

	}
	ky = find_custom_key(info->env_vars, info->args[1]);
	if (ky == NULL)
	{
		print_custom_error(info, ": No variable unset");
		return;
	}
	for (x = 0; info->env_vars[x] != NULL; x++)
		;
	newenv = malloc(sizeof(char *) * x);
	if (newenv == NULL)
	{
		print_custom_error(info, NULL);
		info->exit_code = 127;
		exit_shell(info);
	}
	for (x = 0; info->env_vars[x] != *ky; x++)
		newenv[x] = info->env_vars[x];
	for (y = x + 1; info->env_vars[y] != NULL; y++, x++)
		newenv[x] = info->env_vars[y];
	newenv[x] = NULL;
	free(*ky);
	free(info->env_vars);
	info->env_vars = newenv;
	info->exit_code = 0;
}
