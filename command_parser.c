#include "main.h"

/**
 * parse_cmd - function that parse command line.
 * @dcshell: shell structure.
 * @usrinput: input string.
 *
 * Return: 0 to exit, 1 to continue
 */
int parse_cmd(shell_t *dcshell, char *usrinput)
{
	int shloop;

	dcshell->user_input = non_printed(usrinput);
	dcshell->args = parse_cmdline(dcshell->user_input);
	shloop = find_command(dcshell);
	free(dcshell->args);

	switch (shloop)
	{
		case 0:
			return (0);
		default:
			return (1);
	}
}

/**
 * parse_cmdline - function that tokenizes the
 * input string.
 * @usrinput: input string.
 *
 * Return: parsed string.
 */
char **parse_cmdline(char *usrinput)
{
	char **str_tokens;
	char *str_token;
	size_t i, buffer_size;

	str_tokens = malloc((256) * sizeof(char *));
	if (str_tokens == NULL)
	{
		exit(1);
	}

	str_token = strtok(usrinput, " \t\r\n\a");
	str_tokens[0] = str_token;

	i = 1;
	while (str_token != NULL)
	{
		if (i == buffer_size)
		{
			buffer_size = buffer_size + 256;
			str_tokens = _reallocmdp(str_tokens, i, buffer_size * sizeof(char *));
			if (str_tokens == NULL)
			{
				exit(1);
			}
		}

		str_token = strtok(NULL, " \t\r\n\a");
		str_tokens[i] = str_token;
		i++;
	}

	return (str_tokens);
}

