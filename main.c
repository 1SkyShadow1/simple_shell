#include "shell.h"

/**
 * sig_handler - Handles ^C signal interrupt
 * @unused_var: Unused variable (required for signal function prototype)
 */
static void sig_handler(int unused_var)
{
	unsigned int sig_flag = 0;
	(void)unused_var;
	if (sig_flag == 0)
		print_custom_string("\n$ ");
	else
		print_custom_string("\n");
}

/**
 * main - Main function for the custom shell
 * @argc: Number of arguments passed to main
 * @argv: Array of arguments passed to main
 * @environment: Array of environment variables
 * Return: 0 or exit status, or ?
 */
int main(int argc __attribute__((unused)), char **argv, char **environment)
{

	size_t buffer_len = 0;
	unsigned int is_pipe = 0, i;
	shell_info_t info = {NULL, NULL, NULL, 0, NULL, 0, NULL};

	info.init_args = argv;
	info.env_vars = create_shell_environment(environment);
	signal(SIGINT, sig_handler);
	if (!isatty(STDIN_FILENO))
		is_pipe = 1;
	if (is_pipe == 0)
		print_custom_string("$ ");

	while (getline(&(info.cmd_buffer), &buffer_len, stdin) != -1)
	{
		info.cmd_count++;
		info.cmd_list = tokenize_command(info.cmd_buffer, ";");
		for (i = 0; info.cmd_list && info.cmd_list[i] != NULL; i++)
		{
			info.args = tokenize_command(info.cmd_list[i], "\n \t\r");
			if (info.args && info.args[0])
			{
				if (identify_shell_builtin(&info) == NULL)
					check_executable_path(&info);
			}
			free(info.args);
		}
		free(info.cmd_buffer);
		free(info.cmd_list);

		if (is_pipe == 0)
			print_custom_string("$ ");
		info.cmd_buffer = NULL;
	}
	if (is_pipe == 0)
		print_custom_string("\n");
	destroy_shell_environment(info.env_vars);
	free(info.cmd_buffer);
	exit(info.exit_code);
}
