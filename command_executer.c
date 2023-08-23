#include "main.h"

/**
 * find_command - function that finds builtin commands.
 * @dcshell: shell structure.
 *
 * Return: 1 on success.
 */
int find_command(shell_t *dcshell)
{
	int (*builtin_call)(shell_t *dcshell);

	if (dcshell->args[0] == NULL)
	{
		return (1);
	}

	builtin_call = builtins(dcshell->args[0]);
	if (builtin_call != NULL)
	{
		return (builtin_call(dcshell));
	}

	return (execute_cmd(dcshell));
}

/**
 * execute_cmd - function that execute command lines.
 * @dcshell: shell struct.
 *
 * Return: 1 on success.
 */
int execute_cmd(shell_t *dcshell)
{
	int shell_state, exe;
	pid_t _pid, _mypid;
	char *directory;

	UNUSED(_mypid);

	exe = isexe(dcshell);
	switch (exe)
	{
		case 0:
			directory = _cmd_location(dcshell->args[0], dcshell->_environ);
			if (chk_cmd_err(directory, dcshell) == 1)
				return (1);
			break;
		case -1:
			return (1);
	}

	_pid = fork();
	switch (_pid)
	{
		case 0:
			if (exe == 0)
				directory = _cmd_location(dcshell->args[0], dcshell->_environ);
			else
				directory = dcshell->args[0];
			execve(directory + exe, dcshell->args, dcshell->_environ);
			break;
		case -1:
			perror(dcshell->av[0]);
			return (1);
		default:
			do {
				_mypid = waitpid(_pid, &shell_state, WUNTRACED);
			} while (!WIFEXITED(shell_state) && !WIFSIGNALED(shell_state));
	}

	dcshell->shell_status = shell_state / 256;
	return (1);
}

/**
 * isexe - function that check if file is an executable,
 * @dcshell: shell structure.
 *
 * Return: 0 if is not an executable, other number if is.
 */
int isexe(shell_t *dcshell)
{
	int i = 0, j;
	char *userinput;
	struct stat st;

	userinput = dcshell->args[0];

	while (userinput[i])
	{
		if (userinput[i] == 46)
		{
			if (userinput[i + 1] == 46)
			{
				return (0);
			}
			if (userinput[i + 1] == 47)
			{
				continue;
			}
			else
			{
				break;
			}
		}
		else if (userinput[i] == 47 && i != 0)
		{
			if (userinput[i + 1] == 46)
			{
				continue;
			}
			i++;
			break;
		}
		else
		{
			break;
		}
		i++;
	}

	j = i;

	if (j == 0)
	{
		return (0);
	}

	if (stat(userinput + i, &st) == 0)
	{
		return (i);
	}
	errors(dcshell, 127);

	return (-1);
}

/**
 * _cmd_location - function that locates the command.
 * @command: command, ex: ls.
 * @_environ: environment variable.
 *
 * Return: location of the command, or NULL if cannot found.
 */
char *_cmd_location(char *command, char **_environ)
{
	int index = 0, dir_len, cmd_len;
	char *cmd_path, *path_ptr, *path_token, *directory;
	struct stat st;

	cmd_path = _envir("PATH", _environ);
	if (cmd_path)
	{
		path_ptr = _strdup(cmd_path);
		cmd_len = _strlen(command);
		path_token = _strtok(path_ptr, ":");

		for (; path_token != NULL;)
		{
			if (isdir(cmd_path, &index))
			{
				if (stat(command, &st) == 0)
					return (command);
			}

			dir_len = _strlen(path_token);
			directory = malloc(cmd_len + 2 + dir_len);
			_strcpy(directory, path_token);
			_strcat(directory, "/");
			_strcat(directory, command);
			_strcat(directory, "\0");

			if (stat(directory, &st) == 0)
			{
				free(path_ptr);
				return (directory);
			}
			free(directory);
			path_token = _strtok(NULL, ":");
		}

		free(path_ptr);
		if (stat(command, &st) == 0)
		{
			return (command);
		}

		return (NULL);
	}

	if (command[0] == 47)
	{
		if (stat(command, &st) == 0)
			return (command);
	}

	return (0);
}

/**
 * isdir - function that checks if cmd is in the
 * current directory.
 * @path: pointer to the path of command.
 * @index: pointer of index.
 *
 * Return: 1 if the path is searchable in the cd,
 * 0 otherwise.
 */
int isdir(char *path, int *index)
{
	if (path[*index] == 58)
	{
		return (1);
	}

	for (; path[*index] != 58 && path[*index];)
	{
		*index = *index + 1;
	}

	if (path[*index])
	{
		*index = *index + 1;
	}

	return (0);
}

