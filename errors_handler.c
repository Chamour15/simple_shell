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
	int cd_check = _strcmp("cd", dcshell->args[0]);
	char *err;

	if (error == 127)
	{
		err = not_found404(dcshell);
	}
	if (error == -1)
	{
		err = env_error(dcshell);
	}
	if (error == 2)
	{
		if (cd_check == 0)
		{
			err = cd_error(dcshell);
		}
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
	char *err, *str = _itoa(dcshell->line_counter);
	int strlnegth;

	strlnegth = _strlen(dcshell->av[0]) + _strlen(str);
	strlnegth = strlnegth + _strlen(dcshell->args[0]) + 18;

	err = malloc((strlnegth + 1) * sizeof(char));
	if (err == 0)
	{
		free(err);
		free(str);
		return (NULL);
	}

	_strcpy(err, dcshell->av[0]);
	_strcat(err, ": ");
	_strcat(err, str);
	_strcat(err, ": ");
	_strcat(err, dcshell->args[0]);
	_strcat(err, ": not found\n");
	_strcat(err, "\0");
	free(str);
	return (err);
}

/**
 * env_error - function that show setenv and unseten error msg .
 * @dcshell: shell struct.
 *
 * Return: error message if there is error.
 */
char *env_error(shell_t *dcshell)
{
	char *err;
	char *str = _itoa(dcshell->line_counter);
	char *message = ": Unable to add or change or remove env\n";
	int len;

	len = _strlen(dcshell->av[0]) + _strlen(str);
	len = len + _strlen(dcshell->args[0]) + _strlen(message) + 5;

	err = malloc((len + 1) * sizeof(char));
	if (err == 0)
	{
		free(err);
		free(str);
		return (NULL);
	}

	_strcpy(err, dcshell->av[0]);
	_strcat(err, ": ");
	_strcat(err, str);
	_strcat(err, ": ");
	_strcat(err, dcshell->args[0]);
	_strcat(err, message);
	_strcat(err, "\0");
	free(str);

	return (err);
}

/**
 * cd_error - function that get error message.
 * @dcshell: shell struct.
 *
 * Return: error message to the user command line.
 */
char *cd_error(shell_t *dcshell)
{
	char *err, *message, *str = _itoa(dcshell->line_counter);
	int id, len;

	if (dcshell->args[1][0] == '-')
	{
		message = ": Not a legal option ";
		id = 2;
	}
	else
	{
		message = ": can't cd to given directory ";
		id = _strlen(dcshell->args[1]);
	}

	len = _strlen(dcshell->av[0]) + _strlen(dcshell->args[0]);
	len = len + _strlen(str) + _strlen(message) + id + 6;

	err = malloc((len + 1) * sizeof(char));
	if (err == 0)
	{
		free(str);
		return (NULL);
	}

	err = cd_error2(dcshell, message, err, str);
	free(str);

	return (err);
}

