#include "main.h"

/**
 * cd_error2 - function that concatenates the message
 * for cd_error function.
 * @dcshell: shell struct.
 * @msg: message to show to the user.
 * @err: output message.
 * @str: line of string.
 *
 * Return: error message.
 */
char *cd_error2(shell_t *dcshell, char *msg, char *err, char *str)
{
	char *invalid;

	_strcpy(err, dcshell->av[0]);
	_strcat(err, ": ");
	_strcat(err, str);
	_strcat(err, ": ");
	_strcat(err, dcshell->args[0]);
	_strcat(err, msg);

	if (dcshell->args[1][0] == '-')
	{
		invalid = malloc(3);
		invalid[0] = '-';
		invalid[1] = dcshell->args[1][1];
		invalid[2] = '\0';
		_strcat(err, invalid);
		free(invalid);
	}
	else
	{
		_strcat(err, dcshell->args[1]);
	}

	_strcat(err, "\n");
	_strcat(err, "\0");
	return (err);
}

/**
 * path_error - error message for path.
 * @dcshell: shell struct.
 *
 * Return: error string.
 */
char *path_error(shell_t *dcshell)
{
	char *err, *str = _itoa(dcshell->line_counter);
	int len = _strlen(dcshell->av[0]) + _strlen(str);

	len = len + _strlen(dcshell->args[0]) + 25;

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
	_strcat(err, ": Permission denied\n");
	_strcat(err, "\0");
	free(str);

	return (err);
}

/**
 * exit_error - error message for exit shell
 * @dcshell: shell struct.
 *
 * Return: error message
 */
char *exit_error(shell_t *dcshell)
{
	char *err, *str = _itoa(dcshell->line_counter);
	int len = _strlen(dcshell->av[0]) + _strlen(str);

	len += _strlen(dcshell->args[0]) + _strlen(dcshell->args[1]) + 23;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(str);
		return (NULL);
	}

	_strcpy(err, dcshell->av[0]);
	_strcat(err, ": ");
	_strcat(err, str);
	_strcat(err, ": ");
	_strcat(err, dcshell->args[0]);
	_strcat(err, ": Illegal number: ");
	_strcat(err, dcshell->args[1]);
	_strcat(err, "\n\0");
	free(str);

	return (err);
}

