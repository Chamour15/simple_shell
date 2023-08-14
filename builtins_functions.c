#include "main.h"

/**
 * *builtins - function that call the builtin command.
 * @command: the command that user typed.
 *
 * Return: the builtin command.
 */
int (*builtins(char *command))(shell_t *)
{
	int i = 0, bcmp;

	builtins_t builtins[] = {
		{"exit", shell_exit},
		{"env", print_env},
		{NULL, NULL},
	};

	while (builtins[i].command_name)
	{
		bcmp = _strcmp(builtins[i].command_name, command);
		if (bcmp == 0)
		{
			break;
		}

		i++;
	}

	return (builtins[i].function);
}

/**
 * shell_exit - function that exits the shell prompt.
 * @dcshel: shell struct.
 *
 * Return: 0 on success, 1 on failure.
 */
int shell_exit(shell_t *dcshel)
{
	unsigned int estate;
	char *arg;

	arg = dcshel->args[1];
	if (arg != NULL)
	{
		estate = _atoi(dcshel->args[1]);
		dcshel->shell_status = (estate % 256);
	}

	return (0);
}

