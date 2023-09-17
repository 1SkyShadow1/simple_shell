#include <shell.h>

/**
 * print_custom_string - writes a string to standard output
 * @str: string to write
 *
 * Return: number of characters printed or -1 on failure
 */
ssize_t print_custom_string(char *str)
{
	ssize_t num, len;

	num = custom_string_length(str);
	len = write(STDOUT_FILENO, str, num);
	if (len != num)
	{
		perror("Fatal Error");
		return (-1);
	}
	return (len);
}

/**
 * duplicate_custom_string - returns a pointer to new memory
 * allocation containing a copy
 * @str_to_duplicate: string to be duplicated
 * Return: a pointer to the new duplicated string
 */
char *duplicate_custom_string(char *str_to_duplicate)
{
	char *copy;
	int len, x;

	if (str_to_duplicate == 0)
		return (NULL);

	for (len = 0; str_to_duplicate[len]; len++)
		;
	copy = malloc((len + 1) * sizeof(char));

	for (x = 0; x <= len; x++)
		copy[x] = str_to_duplicate[x];

	return (copy);
}

/**
 * compare_custom_strings - compares two strings
 * @str1: first string, of two to be compared in length
 * @str2: second string, of two, to be compared
 * Return: 0 on success, anything else is a failure
 */
int compare_custom_strings(char *str1, char *str2)
{
	int x;

	x = 0;
	while (str1[x] == str2[x])
	{
		if (str1[x] == '\0')
			return (0);
		x++;
	}
	return (str1[x] - str2[x]);
}

/**
 * concatenate_custom_strings - concatenates two strings
 * @str1: first string
 * @str2: second string
 * Return: pointer
 */
char *concatenate_custom_strings(char *str1, char *str2)
{
	char *new_string;
	unsigned int len1, len2, new_length, x, y;

	len1 = 0;
	len2 = 0;
	if (str == NULL)
		len1 = 0;
	else
	{
		for (len1 = 0; str1[len1]; len1++)
			;
	}
	if (str2 == NULL)
		len2 = 0;
	else
	{
		for (len2 = 0; str2[len2; len2++])
			;
	}
	new_length = len1 + len2 + 2;
	new_string = malloc(new_length * sizeof(char));
	if (new_string == NULL)
		return (NULL);
	for (x = 0; x < len1; x++)
		new_string[x] = str1[x];
	new_string[x] = '/';
	for (y = 0; y < len2; y++)
		new_string[x + 1 + y] = str2[y];
	new_string[len1 + len2 + 1] = '\0';
	return (new_string);
}

/**
 * custom_string_length - returns the length of a string
 * @str: string to be measured
 * Return: length of string
 */
unsigned int custom_string_length(char *str)
{
	unsigned int len;

	len = 0;

	for (len = 0; str[len]; len++)
		;
	return (len);
}

