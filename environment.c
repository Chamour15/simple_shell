#include "main.h"

/**
 * _envir - function that get an environment variable.
 * @envname: name of the environment variable.
 * @_environ: environment variable.
 *
 * Return: value of the environment variable.
 */
char *_envir(const char *envname, char **_environ)
{
	int i = 0, j = 0, env = 0;
	char *envptr = NULL;
	const char *cmpenv;

	while (_environ[i])
	{
		cmpenv = _environ[i];
		while (cmpenv[j] != '=')
		{
			if (cmpenv[j] != envname[j])
			{
				env = 0;
				break;
			}
			env = j + 1;
			j++;
		}

		if (env)
		{
			envptr = _environ[i];
			break;
		}
		i++;
	}

	return (envptr + env);
}

/**
* print_env - function that prints the evironment
* variables.
* @dcshell: data relevant.
*
* Return: 1 on success.
*/

int print_env(shell_t *dcshell)
{
	int i = 0, j;

	while (dcshell->_environ[i])
	{

		for (j = 0; dcshell->_environ[i][j]; j++)
			;

		write(STDOUT_FILENO, dcshell->_environ[i], j);
		write(STDOUT_FILENO, "\n", 1);

		i++;
	}

	dcshell->shell_status = 0;

	return (1);
}

/**
 * _setenv - function that sets an environment variable.
 * @dcshell: shell struct.
 *
 * Return: 1 on success, error message on failure.
 */
int _setenv(shell_t *dcshell)
{
	shell_t *dcsh;
	char *varname, *varvalue, *envvar, *envname;
	int i, envcmp;

	if (dcshell->args[1] == NULL || dcshell->args[2] == NULL)
	{
		errors(dcshell, -1);
		return (1);
	}

	varname = dcshell->args[1];
	varvalue = dcshell->args[2];
	dcsh = dcshell;

	i = 0;
	while (dcsh->_environ[i])
	{
		envvar = _strdup(dcsh->_environ[i]);
		envname = _strtok(envvar, "=");
		envcmp = _strcmp(envname, varname);
		if (envcmp == 0)
		{
			free(dcsh->_environ[i]);
			dcsh->_environ[i] = create_env(envname, varvalue);
			free(envvar);
			return (1);
		}
		free(envvar);
		i++;
	}

	dcsh->_environ = _reallocmdp(dcsh->_environ, i, sizeof(char *) * (i + 2));
	dcsh->_environ[i] = create_env(varname, varvalue);
	dcsh->_environ[i + 1] = NULL;

	return (1);
}

/**
 * _unsetenv - function that remove the environment variable.
 * @dcshell: shell struct.
 *
 * Return: 1 on success, error message on failure..
 */
int _unsetenv(shell_t *dcshell)
{
	char **envrel;
	int i, j, check = -1;
	char *varenv;

	if (dcshell->args[1] == NULL)
	{
		errors(dcshell, -1);
		return (1);
	}
	for (i = 0; dcshell->_environ[i]; i++)
	{
		varenv = _strdup(dcshell->_environ[i]);
		if (_strcmp(_strtok(varenv, "="), dcshell->args[1]) == 0)
		{
			check = i;
		}
		free(varenv);
	}
	if (check == -1)
	{
		errors(dcshell, -1);
		return (1);
	}
	envrel = malloc((i + 1) * sizeof(char *));
	if (envrel == NULL)
	{
		free(envrel);
		return (0);
	}
	for (i = j = 0; dcshell->_environ[i]; i++)
	{
		if (i != check)
			envrel[j++] = dcshell->_environ[i];
	}
	envrel[j] = NULL;
	free(dcshell->_environ[check]);
	free(dcshell->_environ);
	dcshell->_environ = envrel;
	return (1);
}

/**
 * create_env - function to store new env var in memory.
 * a new env or alias
 * @envname: name (env or alias)
 * @envval: value (env or alias)
 *
 * Return: new environment variable.
 */
char *create_env(char *envname, char *envval)
{
	char *create;
	int envlen = _strlen(envname), vallen = _strlen(envval);

	create = malloc((envlen + vallen + 2) * sizeof(char));
	if (create == NULL)
	{
		free(create);
		return (NULL);
	}

	_strcpy(create, envname);
	_strcat(create, "=");
	_strcat(create, envval);
	_strcat(create, "\0");

	return (create);
}

