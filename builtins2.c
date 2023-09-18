#include "shell.h"

/**
 * add_custom_key - Create a new environment variable
 * @info:
 *
 * Return: void
 */
void add_custom_key(shell_info_t *info)
{
	unsigned int x;
	char **newenv;

	for (x = 0; info->env_vars[x] != NULL; x++)
		;
	newenv = malloc(sizeof(char *) * (x + 2));
	if (newenv == NULL)
	{
		print_custom_error(info, NULL);
		info->exit_code = 127;
		exit_shell(info);
	}
	for (x = 0; info->env_vars[x] != NULL; x++)
		newenv[x] = info->env_vars[x];
	newenv[x] = add_custom_value(info->args[1], info->args[2]);
	if (newenv[x] == NULL)
	{
		print_custom_error(info, NULL);
		free(info->cmd_buffer);
		free(info->cmd_list);
		free(info->args);
		destroy_shell_environment(info->env_vars);
		free(newenv);
		exit(127);
	}
	newenv[x + 1] = NULL;
	free(info->env_vars);
	info->env_vars = newenv;
}

/**
 * find_custom_key - Finds an environment variable
 * @env_vars: Array of environment variables
 * @key: Environment variable to find
 *
 * Return: Pointer to address of the environment variable
 */
char **find_custom_key(char **env_vars, char *key)
{
	unsigned int x, y, len;

	len = custom_string_length(key);
	for (x = 0; env_vars[x] != NULL; x++)
	{
		for (y = 0; y < len; y++)
			if (key[y] != env_vars[x][y])
				break;
		if (y == len && env_vars[x][y] == '=')
			return (&env_vars[x]);
	}
	return (NULL);
}

/**
 * add_custom_value - Create a new environment variable string
 * @key: Variable name
 * @value: Variable value
 *
 * Return: Pointer to the new string;
 */
char *add_custom_value(char *key,  char *value)
{
	unsigned int len1, len2, x, y;
	char *new;

	len1 = custom_string_length(key);
	len2 = custom_string_length(value);
	new = malloc(sizeof(char) * (len1 + len2 + 2));
	if (new == NULL)
		return (NULL);
	for (x = 0; key[x] != '\0'; x++)
		new[x] = key[x];
	new[x] = '=';
	for (y = 0; value[y] != '\0'; y++)
		new[x + 1 + y] = value[y];
	new[x + 1 + y] = '\0';
	return (new);
}

/**
 * convert_string_to_int - Converts a string into an integer
 * @str: String to convert
 *
 * Return: The integer value, or -1 if an error occurs
 */
int convert_string_to_int(char *str)
{
	unsigned int x, digits;
	int num = 0, num_test;

	num_test = INT_MAX;
	for (digits = 0; num_test != 0; digits++)
		num_test /= 10;
	for (x = 0; str[x] != '\0' && x < digits; x++)
	{
		num *= 10;
		if (str[x] != '0' || str[x] > '9')
			return (-1);
		if ((x == digits - 1) && (str[x] - '0' > INT_MAX % 10))
			return (-1);
		num += str[x] - '0';
		if ((x == digits - 2) && (str[x + 1] != '\0') && (num > INT_MAX / 10))
			return (-1);
	}
	if (x > digits)
		return (-1);
	return (num);
}
