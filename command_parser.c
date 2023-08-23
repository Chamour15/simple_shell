#include "main.h"

/**
 * parse_cmd - function that parse command line.
 * @dcshell: shell structure.
 * @usrinput: input string.
 *
 * Return: exit on 0, 1 to continue
 */
int parse_cmd(shell_t *dcshell, char *usrinput)
{
	int shloop;
	separator_t *sephead = NULL, *seplist;
	cmdline_t *cmdhead = NULL, *cmdlist;

	node(&sephead, &cmdhead, usrinput);
	seplist = sephead;
	cmdlist = cmdhead;

	for (; cmdlist != NULL;)
	{
		dcshell->user_input = cmdlist->cmd_line;
		dcshell->args = parse_cmdline(dcshell->user_input);
		shloop = find_command(dcshell);
		free(dcshell->args);

		if (shloop == 0)
		{
			break;
		}

		next_cmd(&seplist, &cmdlist, dcshell);
		if (cmdlist != NULL)
		{
			cmdlist = cmdlist->next;
		}
	}

	free_sep(&sephead);
	free_cmdline(&cmdhead);

	switch (shloop)
	{
		case 0:
			return (0);
		default:
			return (1);
	}
}

/**
 * parse_cmdline - function that tokenizes the
 * input string.
 * @usrinput: input string.
 *
 * Return: parsed string.
 */
char **parse_cmdline(char *usrinput)
{
	char **str_tokens;
	char *str_token;
	size_t i, buffer_size = 128;

	str_tokens = malloc((buffer_size) * sizeof(char *));
	if (str_tokens == NULL)
	{
		exit(EXIT_FAILURE);
	}

	str_token = _strtok(usrinput, " \t\r\n\a");
	str_tokens[0] = str_token;

	for (i = 1; str_token != NULL; i++)
	{
		if (i == buffer_size)
		{
			buffer_size = buffer_size + buffer_size;
			str_tokens = _reallocmdp(str_tokens, i, sizeof(char *));
			if (str_tokens == NULL)
			{
				exit(EXIT_FAILURE);
			}
		}

		str_token = _strtok(NULL, " \t\r\n\a");
		str_tokens[i] = str_token;
	}

	return (str_tokens);
}

/**
 * node - function that adds separators and command line.
 * @shead: head of separator single linked list.
 * @chead: head of command line single linked list.
 * @userinput: input string from user.
 *
 * Return: void, no return.
 */
void node(separator_t **shead, cmdline_t **chead, char *userinput)
{
	char *cmdline;
	int i;

	userinput = non_printed(userinput);

	i = 0;
	while (userinput[i])
	{
		if (userinput[i] == ';')
		{
			sep_end(shead, userinput[i]);
		}
		if (userinput[i] == '|' || userinput[i] == '&')
		{
			sep_end(shead, userinput[i]);
			i++;
		}
		i++;
	}

	cmdline = _strtok(userinput, ";|&");

	do {
		cmdline = non_printed2(cmdline);
		line_end(chead, cmdline);
		cmdline = _strtok(NULL, ";|&");
	} while (cmdline != NULL);
}

/**
 * next_cmd - function that gets the next command line.
 * @slist: separator list.
 * @clist: command line list.
 * @dcshell: shell struct.
 *
 * Return: void, no return
 */
void next_cmd(separator_t **slist, cmdline_t **clist, shell_t *dcshell)
{
	cmdline_t *cmd_l = *clist;
	separator_t *sep_l = *slist;
	int i, status = dcshell->shell_status;

	for (i = 1; i && sep_l != NULL;)
	{
		if (status == 0)
		{
			if (sep_l->sep == '&' || sep_l->sep == ';')
			{
				i = 0;
			}
			if (sep_l->sep == '|')
			{
				cmd_l = cmd_l->next, sep_l = sep_l->next;
			}
		}
		else
		{
			if (sep_l->sep == '|' || sep_l->sep == ';')
			{
				i = 0;
			}
			if (sep_l->sep == '&')
			{
				cmd_l = cmd_l->next, sep_l = sep_l->next;
			}
		}
		if (!i && sep_l != NULL)
		{
			sep_l = sep_l->next;
		}
	}
	*slist = sep_l;
	*clist = cmd_l;
}

