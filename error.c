#include "shell.h"

/**
 * print_custom_error - Prints error messages to standard error
 * @info: Pointer to shell information structure
 * @msg: Message to print
 *
 * Return: void
 */
void print_custom_error(shell_info_t *info, char *msg)
{
	char *count;

	print_custom_string(info->init_args[0]);
	print_custom_string(": ");
	count = int_to_custom_string(info->cmd_count);
	print_custom_string(count);
	free(count);
	print_custom_string(": ");
	print_custom_string(info->args[0]);
	if (msg)
	{
		print_custom_string(msg);
	}
	else
		perror("");
}

/**
 * print_custom_error_message - Prints a string to standard error
 * @str: String to print
 *
 * Return: void
 */
void print_custom_error_message(char *str)
{
	ssize_t num, len;

	num = custom_string_length(str);
	len = write(STDERR_FILENO, str, num);
	if (len != num)
	{
		perror("Fatal Error");
		exit(1);
	}
}

/**
 * int_to_custom_string - CConverts an unsigned int to a string
 * @value: Unsigned int to convert
 *
 * Return: Pointer to the converted string
 */
char *int_to_custom_string(unsigned int value)
{
	char *numstr;
	unsigned int tmp, digits;

	tmp = value;
	for (digits = 0; tmp != 0; digits++)
		tmp /= 10;
	numstr = malloc(sizeof(char) * (digits + 1));
	if (numstr == NULL)
	{
		perror("Fatal Error1");
		exit(127);
	}
	numstr[digits] = '\0';
	for (--digits; value; --digits)
	{
		numstr[digits] = (value % 10) + '0';
		value /= 10;
	}
	return (numstr);
}
