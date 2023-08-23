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
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{"cd", change_dir},
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
	int allowed, strlen, num;
	unsigned int estate;
	char *arg;

	arg = dcshel->args[1];
	if (arg != NULL)
	{
		allowed = _isdigit(dcshel->args[1]);
		estate = _atoi(dcshel->args[1]);
		strlen = _strlen(dcshel->args[1]);
		num = estate > (unsigned int)INT_MAX;
		if (strlen > 10 || num || !allowed)
		{
			errors(dcshel, 2);
			dcshel->shell_status = 2;
			return (1);
		}
		dcshel->shell_status = (estate % 256);
		free(arg);
	}

	return (0);
}

/**
 * change_dir - function that changes current directory.
 * @dcshell: shell struct.
 *
 * Return: Always 1.
 */
int change_dir(shell_t *dcshell)
{
	char *dir = dcshell->args[1];

	if (dir == NULL || strcmp(dir, "$HOME") == 0 || strcmp(dir, "--") == 0)
	{
		go_home(dcshell);
		return (1);
	}
	else if (strcmp(dir, "-") == 0)
	{
		go_back(dcshell);
		return (1);
	}

	cd(dcshell);
	return (1);
}

/**
 * go_home - function that changes current dir
 * to home directory.
 *@dcshell: shell struct.
 *
 *Return: void, no return.
 */
void go_home(shell_t *dcshell)
{

	char _pwd[PATH_MAX];
	char *_home = get_cdenv("HOME", dcshell->_environ);

	getcwd(_pwd, sizeof(_pwd));

	if (_home == NULL || chdir(_home) == -1)
	{
		errors(dcshell, 2);
	}
	else
	{
		cd_env("OLDPWD", _pwd, dcshell);
		cd_env("PWD", _home, dcshell);
	}

	dcshell->shell_status = 0;
}

/**
 * go_back - function that changes current dir to the
 * previous dir.
 * @dcshell: shell struct.
 *
 * Return: void, no return.
 */
void go_back(shell_t *dcshell)
{
	char *_pwdp, *_old_pwdp, *c_pwdp, *c_old_pwdp;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	c_pwdp = _strdup(pwd);
	_old_pwdp = get_cdenv("OLDPWD", dcshell->_environ);

	if (_old_pwdp == NULL)
	{
		c_old_pwdp = c_pwdp;
	}
	else
	{
		c_old_pwdp = _strdup(_old_pwdp);
	}

	cd_env("OLDPWD", c_pwdp, dcshell);

	switch (chdir(c_old_pwdp))
	{
		case -1:
			cd_env("PWD", c_pwdp, dcshell);
			break;
		default:
			cd_env("PWD", c_old_pwdp, dcshell);
	}

	_pwdp = get_cdenv("PWD", dcshell->_environ);
	write(STDOUT_FILENO, _pwdp, _strlen(_pwdp));
	write(STDOUT_FILENO, "\n", 1);
	free(c_pwdp);

	if (_old_pwdp)
	{
		free(c_old_pwdp);
	}
	dcshell->shell_status = 0;
	chdir(_pwdp);
}

