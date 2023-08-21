#include "main.h"

/**
 * cd_env - function that sets an environment variable for cd function.
 * @envname: environment variable name pwd, oldpwd, home.
 * @envvalue: environment variable value.
 * @dcsh: shell struct.
 *
 * Return: void, no return.
 */
void cd_env(char *envname, char *envvalue, shell_t *dcsh)
{
	char *envvar, *_envname;
	int i = 0, cmp;

	while (dcsh->_environ[i])
	{
		envvar = _strdup(dcsh->_environ[i]);
		_envname = _strtok(envvar, "=");
		cmp = _strcmp(_envname, envname);
		if (cmp == 0)
		{
			free(dcsh->_environ[i]);
			dcsh->_environ[i] = create_env(_envname, envvalue);
			free(envvar);
			return;
		}
		free(envvar);
		i++;
	}

	dcsh->_environ = _reallocmdp(dcsh->_environ, i, (i + 2) * sizeof(char *));
	dcsh->_environ[i] = create_env(envname, envvalue);
	dcsh->_environ[i + 1] = NULL;
}

/**
 * cd - function that changes current directory
 * to a directory given by the user
 * @dcshell: shell struct.
 *
 * Return: void, no return
 */
void cd(shell_t *dcshell)
{
	char *directory, *_pwdp, *cdir;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	directory = dcshell->args[1];
	if (chdir(directory) == -1)
	{
		errors(dcshell, 2);
		return;
	}

	_pwdp = _strdup(pwd);
	cd_env("OLDPWD", _pwdp, dcshell);
	cdir = _strdup(directory);
	cd_env("PWD", cdir, dcshell);
	free(_pwdp);
	free(cdir);
	dcshell->shell_status = 0;
	chdir(directory);
}

/**
 * cmp_env - function that compares environment
 * variables names, with the given name.
 * @envname: name of the environment variable
 * @pname: name passed to.
 *
 * Return: 0 if are not equal. i + 1 if not.
 */
int cmp_env(const char *envname, const char *pname)
{
	int i = 0;

	while (envname[i] != '=')
	{
		if (envname[i] != pname[i])
		{
			return (0);
		}
		i++;
	}

	return (i + 1);
}

/**
 * get_cdenv - function to get an environment
 * for cd.
 * @envname: environment variable name.
 * @_environ: environment variable.
 *
 * Return: environment variable value, or null
 * if not found.
 */
char *get_cdenv(const char *envname, char **_environ)
{
	char *env = NULL;
	int i = 0, j = 0;

	while (_environ[i])
	{
		j = cmp_env(_environ[i], envname);
		if (j)
		{
			env = _environ[i];
			break;
		}
		i++;
	}

	return (env + j);
}

