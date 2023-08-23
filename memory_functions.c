#include "main.h"

/**
 * _memcpy - function that copies memory between pointers.
 * @destptr: destination pointer.
 * @srcptr: source pointer.
 * @sizep: size of the new pointer.
 *
 * Return: void, no return.
 */
void _memcpy(void *destptr, const void *srcptr, unsigned int sizep)
{
	char *_destptr = (char *)destptr;
	char *_ptr = (char *)srcptr;

	unsigned int i = 0;

	while (i < sizep)
	{
		_destptr[i] = _ptr[i];
		i++;
	}
}

/**
 * _realloc - function that reallocates a memory.
 * @oldptr: pointer to the previously allocated memory.
 * @old_msize: size, in bytes, of the allocated space.
 * @new_msize: new size, in bytes, of the new memory .
 *
 * Return: if new_msize == old_msize, returns oldptr.
 * if realloc fails, returns NULL.
 */
void *_realloc(void *oldptr, unsigned int old_msize, unsigned int new_msize)
{
	void *new_mptr;

	if (oldptr == NULL)
	{
		return (malloc(new_msize));
	}

	if (new_msize == 0)
	{
		free(oldptr);
		return (NULL);
	}

	if (new_msize == old_msize)
	{
		return (oldptr);
	}

	new_mptr = malloc(new_msize);
	if (new_mptr == NULL)
	{
		return (NULL);
	}

	if (new_msize < old_msize)
	{
		_memcpy(new_mptr, oldptr, new_msize);
	}
	else
	{
		_memcpy(new_mptr, oldptr, old_msize);
	}

	free(oldptr);

	return (new_mptr);
}

/**
 * _reallocmdp - function that reallocates a memory block of a double pointer.
 * @oldmp: double pointer to the memory previously allocated.
 * @old_size: size, in bytes, of the allocated space of ptr.
 * @new_size: new size, in bytes, of the new memory block.
 *
 * Return: if new_msize == old_msize, returns oldmptr without changes.
 * if malloc fails, returns NULL.
 */
char **_reallocmdp(char **oldmp, unsigned int old_size, unsigned int new_size)
{
	unsigned int i;
	char **new_mptr;

	if (oldmp == NULL)
	{
		return (malloc(new_size * sizeof(char *)));
	}

	if (new_size == old_size)
	{
		return (oldmp);
	}

	new_mptr = malloc(new_size * sizeof(char *));
	if (new_mptr == NULL)
	{
		return (NULL);
	}

	i = 0;
	while (i < old_size)
	{
		new_mptr[i] = oldmp[i];
		i++;
	}

	free(oldmp);

	return (new_mptr);
}

/**
 * free_sep - function that frees a separator.
 * singly lnked list.
 * @head: head of the linked list.
 *
 * Return: void, no return.
 */
void free_sep(separator_t **head)
{
	separator_t *current_node, *temp_node;

	if (head != NULL)
	{
		current_node = *head;

		while ((temp_node = current_node) != NULL)
		{
			current_node = current_node->next;
			free(temp_node);
		}

		*head = NULL;
	}
}

/**
 * free_cmdline - function that frees command line.
 * singly linked list.
 * @head: head of the linked list.
 *
 * Return: coid no return.
 */
void free_cmdline(cmdline_t **head)
{
	cmdline_t *current_node, *temp_node;

	if (head != NULL)
	{
		current_node = *head;

		while ((temp_node = current_node) != NULL)
		{
			current_node = current_node->next;
			free(temp_node);
		}

		*head = NULL;
	}
}

