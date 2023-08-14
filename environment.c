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

