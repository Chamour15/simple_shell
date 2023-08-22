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

