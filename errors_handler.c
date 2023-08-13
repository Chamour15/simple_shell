#include "main.h"

/**
 * chk_cmd_err - function that check if there is error.
 * @directory: pointer to the destination directory.
 * @dcshell: shell structure.
 *
 * Return: 1 if there is an error, 0 if not.
 */
int chk_cmd_err(char *directory, shell_t *dcshell)
{
	if (directory == NULL)
	{
		errors(dcshell, 127);
		return (1);
	}

	return (0);
}

/**
 * errors - function that calls the error handler.
 * @dcshell: shell structure.
 * @error: error value.
 *
 * Return: error
 */
int errors(shell_t *dcshell, int error)
{
	char *err;

	if (error == 127)
	{
		err = not_found404(dcshell);
	}

	if (err)
	{
		write(STDERR_FILENO, err, _strlen(err));
		free(err);
	}

	dcshell->shell_status = error;

	return (error);
}

/**
 * not_found404 - function that show error message for command
 * not found.
 * @dcshell: shell struct.
 *
 * Return: error message to show.
 */
char *not_found404(shell_t *dcshell)
{
	char *error;
	int strlnegth;

	strlnegth = _strlen(dcshell->av[0] + 1);
	strlnegth += _strlen(dcshell->args[0]) + 24;

	error = malloc((strlnegth + 1) * sizeof(char));
	if (error == 0)
	{
		free(error);
		return (NULL);
	}

	_strcpy(error, dcshell->av[0]);

	_strcat(error, ": No such file or directory\n");
	_strcat(error, "\0");

	return (error);
}

