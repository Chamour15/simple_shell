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

