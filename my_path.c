#include "shell.h"
/**
 *find_executable_path - gets path variables
 *
 * @env_vars: Array of environment vars
 *
 *Return: pointer to node ontaining PATH
 */

char *find_executable_path(char **env_vars)
{
	char *path = "PATH=";
	unsigned int x, y;

	for (x = 0; env_vars[x] != NULL; x++)
	{
		for (y = 0; path[y] != '\0'; y++)
		{
			if (path[y] != env_vars[x][y])
				break;
		}

		if (path[y] == '\0')
			break;
	}
	return (env_vars[x]);

}


/**
 * execute_shell_command - executes command in the path
 * @command: the full path to command
 * @info: pointer to struct
 *
 * Return: (0)
 */
int execute_shell_command(char *command, shell_info_t *info)
{
	pid_t child_pid;

	if (access(command, X_OK) == 0)
	{
		child_pid = fork();

		if (child_pid == -1)
			print_custom_error(info, NULL);
		if (child_pid == 0)
		{
			if (execve(command, info->args, info->env_vars) == -1)
				print_custom_error(info, NULL);

		}
		else
		{
			wait(&info->exit_code);
			if (WIFEXITED(info->exit_code))
				info->exit_code = WEXITSTATUS(info->exit_code);
			else if (WIFSIGNALED(info->exit_code)
					&& WTERMSIG(info->exit_code) == SIGINT)
				info->exit_code = 130;
			return (0);
		}
		info->exit_code = 127;
		return (1);
	}
	else
	{
		print_custom_error(info, ": permission denied\n");
		info->exit_code = 126;

	}
	return (0);
}

/**
 *check_executable_path - checks if cmd is in path
 *@info: pointer to struct of shell information
 *
 *Return: void
 */
void check_executable_path(chell_info_t *info)
{
	char *path, *path_dup = NULL, check = NULL;
	unsigned int x = 0, n = 0;
	char **path_tokens;
	struct stat buf;

	if (check_directory_existence(info->args[0]))
		n = execute_current_directory(info);
	else
	{
		path = find_directory_existence(info->args[0]);
		if (path != NULL)
		{
			path_dup = duplicate_custom_string(path + 5);
			path_tokens = tokenize_command(path_dup, ":");
			for (x = 0; path_tokens && path_tokens[x]; x++, free(check))
			{
				check = concatenate_custom_strings(path_tokens[x], info->args[0]);
				if (stat(check, &buf) == 0)
				{
					n = execute_shell_command(check, info);
					free(check);
					break;
				}
			}
			free(path_dup);
			if (path_tokens == NULL)
			{
				info->exit_code = 127;
				exit_shell(info);
			}
		}
		if (path == NULL || path_tokens[x] == NULL)
		{
			print_custom_error(info, ": not found\n");
			info->exit_code = 127;
		}
		free(path_tokens);
	}
	if (n == 1)
		exit_shell(info);
}

/**
 * execute_current_directory - executes cmd in current directory
 * @info: points of shell
 *
 * Return: (0) success
 *
 */

int execute_current_directory(shell_info_t *info)
{
	pid_t child_pid;
	struct stat buf;

	if (stat(info->args[0], &buf) == 0)
	{
		if (access(info->args[0], X_OK) == 0)
		{
			child_pid = fork();
			if (child_pid == -1)
				print_custom_error(info, NULL);
			if (child_pid == 0)
			{
				if (execve(info->arg[0], info->args, info->env_vars) == -1)
					print_custom_error(info, NULL);
			}
			else
			{
				wait(&info->exit_code);
				if (WIFEXITED(info->exit_code))
					info->exit_code = WEXITSTATUS(info->exit_code);
				else if (WIFSIGNALED(info->exit_code)
						&& WTERMSIG(info->exit_code) == SIGINT)
					info->exit_code = 130;
				return (0);
			}
			info->exit_code = 127;
			return (1);
		}
		else
		{
			print_custom_error(info, ": permission denied\n");
			info->exit_code = 126;
		}
		return (0);
	}
	print_custom_error(info, ": not found\n");
	info->exit_code = 127;
	return (0);
}

/**
 * check_directory_existence - checks if cmd is part of path
 *@path: cmd
 *
 * Return: (1) successful
 */
int  check_directory_existence(char *path)
{
	unsigned int x;

	x = 0;
	while (path[x])
	{
		if (path[x] == '/')
		{
			return (1);
		}
		x++;
	}

	return (0);
}
