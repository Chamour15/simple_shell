#include "main.h"

void init_shell(shell_t *dcshell, char **av);

/**
 * main - Entry point
 * @ac: command line arguments number (unused).
 * @av: command line arguments.
 *
 * Return: shell_status.
 */
int main(int ac, char **av)
{
	shell_t dcshell, *sh;
	char *user_input;
	int shloop, end_of_file;
	unsigned int i = 0;

	UNUSED(ac);
	init_shell(&dcshell, av);
	sh = &dcshell;
	for (shloop = 1; shloop == 1;)
	{
		write(STDIN_FILENO, "#cisfun$ ", 9);
		user_input = line_reader(&end_of_file);
		if (end_of_file != EOF)
		{
			if (user_input == NULL)
				continue;
			shloop = parse_cmd(sh, user_input);
			sh->line_counter += 1;
			free(user_input);
		}
		else
		{
			shloop = 0;
			free(user_input);
		}
	}
	while (sh->_environ[i])
	{
		free(sh->_environ[i]);
		i++;
	}
	free(sh->pid);
	free(sh->_environ);
	switch (dcshell.shell_status)
	{
		case -1:
			return (255);
		default:
			return (dcshell.shell_status);
	}
}

/**
 * init_shell - Initialize shell structure.
 * @dcshell: shell structure.
 * @av: command line arguments.
 *
 * Return: void, no return.
 */
void init_shell(shell_t *dcshell, char **av)
{
	unsigned int i;

	dcshell->av = av;
	dcshell->shell_status = 0;
	dcshell->user_input = NULL;
	dcshell->line_counter = 1;
	dcshell->args = NULL;

	i = 0;
	while (environ[i])
	{
		i++;
	}

	dcshell->_environ = malloc((i + 1) * sizeof(char *));

	i = 0;
	while (environ[i])
	{
		dcshell->_environ[i] = _strdup(environ[i]);
		i++;
	}

	dcshell->_environ[i] = NULL;
	dcshell->pid = _itoa(getpid());
}

