#include "main.h"

/**
 * line_reader - function that reads the user input string.
 * @end_of_file: return value of getline function
 *
 * Return: user input string.
 */
char *line_reader(int *end_of_file)
{
	size_t buffer_size = 0;
	char *user_input = NULL;

	*end_of_file = getline(&user_input, &buffer_size, stdin);

	return (user_input);
}

