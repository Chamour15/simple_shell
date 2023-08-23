#include "main.h"

/**
 * non_printed - function for non-printed chars.
 * @usrinput: input string.
 *
 * Return: swapped string
 */
char *non_printed(char *usrinput)
{
	int i = 0;

	while (usrinput[i])
	{
		if (usrinput[i] == '|')
		{
			if (usrinput[i + 1] != '|')
			{
				usrinput[i] = 16;
			}
			else
			{
				i++;
			}
		}
		if (usrinput[i] == '&')
		{
			if (usrinput[i + 1] != '&')
			{
				usrinput[i] = 12;
			}
			else
			{
				i++;
			}
		}
		i++;
	}

	return (usrinput);
}

/**
 * non_printed2 - function for non-printed chars.
 * @usrinput: input string.
 *
 * Return: swapped string
 */
char *non_printed2(char *usrinput)
{
	int i = 0;

	while (usrinput[i])
	{
		usrinput[i] = (usrinput[i] == 16 ? '|' : usrinput[i]);
		usrinput[i] = (usrinput[i] == 12 ? '&' : usrinput[i]);
		i++;
	}

	return (usrinput);
}

/**
 * sep_end - function that adds a separator for cmd.
 * @head: head of the linked list.
 * @separator: separator (; | &).
 *
 * Return: pointer to the address of the head.
 */
separator_t *sep_end(separator_t **head, char separator)
{
	separator_t *new_node, *temp_node;

	new_node = malloc(sizeof(separator_t));
	if (new_node == NULL)
	{
		return (NULL);
	}

	new_node->sep = separator;
	new_node->next = NULL;

	temp_node = *head;
	if (temp_node == NULL)
	{
		*head = new_node;
	}
	else
	{
		while (temp_node->next != NULL)
		{
			temp_node = temp_node->next;
		}
		temp_node->next = new_node;
	}

	return (*head);
}

/**
 * line_end - function that adds a command line at the end
 * of a singly linked list.
 * @head: head of the linked list.
 * @cmd: command line.
 *
 * Return: pointer to the address of the head.
 */
cmdline_t *line_end(cmdline_t **head, char *cmd)
{
	cmdline_t *new_node, *temp_node;

	new_node = malloc(sizeof(cmdline_t));
	if (new_node == NULL)
	{
		return (NULL);
	}

	new_node->cmd_line = cmd;
	new_node->next = NULL;

	temp_node = *head;
	if (temp_node == NULL)
	{
		*head = new_node;
	}
	else
	{
		while (temp_node->next != NULL)
		{
			temp_node = temp_node->next;
		}
		temp_node->next = new_node;
	}

	return (*head);
}

/**
 * charcmp - function that compare compare chars of strings
 * @string: input string.
 * @delim: delimiter.
 *
 * Return: 1 if they are equals, 0 if they are not.
 */
int charcmp(char string[], const char *delim)
{
	unsigned int i, j, k, l, m;

	l = 0;
	m = 0;

	for (i = 0, k = 0; string[i]; i++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (string[i] == delim[j])
			{
				k++;
				break;
			}
		}
	}

	l = i;
	m = k;
	if (l == m)
	{
		return (1);
	}
	return (0);
}
