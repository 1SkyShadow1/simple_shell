#include <shell.h>

/**
 * realloc_custom_pointer - Reallocates a pointer to double the space
 * @ptr: Pointer to the old array
 * @size: Pointer to number of elements in the old array
 *
 * Return: Pointer to the new array
 */
char **realloc_custom_pointer(char **ptr, size_t *size)
{
	char **new_ptr;
	size_t x;

	new_ptr = malloc(sizeof(char *) * ((*size) + 10));
	if (new_ptr == NULL)
	{
		free(ptr);
		return (NULL);
	}
	for (x = 0; x < (*size); i++)
	{
		new_ptr[x] = ptr[x];
	}
	*size += 10;
	free(ptr);
	return (new_ptr);
}
