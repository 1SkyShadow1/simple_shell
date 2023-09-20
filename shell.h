#ifndef shell_h
#define shell_h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <limits.h>
#include <signal.h>

/**
 *struct shell_info - struct for shell info
 * @args: command line args
 * @cmd_buffer: buffer for commands
 * @env_vars: Environment vars
 * @cmd_count: count of commands
 * @init_args: args at shell start
 * @exit_code: exit
 * @cmd_list: commands to execute
 */
typedef struct shell_info
{
	char **args;
	char *cmd_buffer;
	char **env_vars;
	size_t cmd_count;
	char **init_args;
	int exit_code;
	char **cmd_list;
} shell_info_t;

/**
 *struct shell_builtin - structure for shell built in function
 *@builtin_name: Name of the custom builtin command
 *@builtin_func: function pointer
 */
typedef struct shell_builtin
{
	char *builtin_name;
	void (*builtin_func)(shell_info_t *);
} shell_builtin_t;

char *custom_strtok_r(char *str, const char *delim);
void (*identify_shell_builtin(shell_info_t *info))(shell_info_t *info);
void exit_shell(shell_info_t *info);
void show_shell_environment(shell_info_t *info);
void set_shell_environment(shell_info_t *info);
void unset_shell_environment(shell_info_t *info);
char **create_shell_environment(char **env_vars);
void destroy_shell_environment(char **env_vars);
ssize_t print_custom_string(char *str);
char *duplicate_custom_string(char *str_to_duplicate);
int compare_custom_strings(char *str1, char *str2);
char *concatenate_custom_strings(char *str1, char *str2);
unsigned int custom_string_length(char *str);
char **tokenize_command(char *cmd_buffer, char *delimeter);
char **realloc_custom_pointer(char **ptr, size_t *size);
void add_custom_key(shell_info_t *info);
char **find_custom_key(char **env_vars, char *key);
char *add_custom_value(char *key, char *value);
int convert_string_to_int(char *str);
void check_executable_path(shell_info_t *info);
int execute_shell_command(char *command, shell_info_t *info);
char *find_executable_path(char **env_vars);
int execute_current_directory(shell_info_t *info);
int check_directory_existence(char *path);
void print_custom_error(shell_info_t *info, char *message);
void print_custom_error_message(char *str);
char *int_to_custom_string(unsigned int value);
#endif
