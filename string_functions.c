#include "main.h"

/**
 * *_strcpy - function that copies the string pointed
 * to by src.
 * @dest: char pointer the dest of the copied string.
 * @src: char pointer the source of string.
 *
 * Return: destination.
 */
char *_strcpy(char *dest, char *src)
{
	size_t i = 0;

	while (src[i] != 0)
	{
		dest[i] = src[i];
		i++;
	}

	dest[i] = 0;

	return (dest);
}

/**
 * _strcat - function that concatenate two strings.
 * @dest: pointer to the destination of the string.
 * @src: pointer to the source of string.
 *
 * Return: destination string.
 */
char *_strcat(char *dest, const char *src)
{
	int i, j = 0;

	for (i = 0; dest[i] != 0; i++)
		;

	while (src[j] != 0)
	{
		dest[i] = src[j];
		i++;
		j++;
	}

	dest[i] = 0;

	return (dest);
}

/**
 * _strdup - function that duplicates a string in memory.
 * @str: pointer to string of character.
 *
 * Return: duplicated string in memory.
 */
char *_strdup(const char *str)
{
	size_t str_len;
	char *new_str;

	str_len = _strlen(str);

	new_str = malloc((str_len + 1) * sizeof(char));
	if (new_str == NULL)
	{
		return (NULL);
	}

	_memcpy(new_str, str, str_len + 1);

	return (new_str);
}

/**
 * _strcmp - function that compares two strings.
 * @s1: the first string.
 * @s2: the second string.
 *
 * Return: 0 if both s1 & s2 are equals, if not 1 or...
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0, j = 0;

	while (j == 0)
	{
		if ((*(s1 + i) == 0) && (*(s2 + i) == 0))
		{
			break;
		}

		j = *(s1 + i) - *(s2 + i);
		i++;
	}

	return (j);
}

/**
 * _strtok - function that splits a string by some delimiter.
 * @string: input string.
 * @delim: delimiter.
 *
 * Return: splited string.
 */
char *_strtok(char *string, const char *delim)
{
	static char *index;
	int i;

	if (string != NULL)
		index = string;
	else
		string = index;

	if (*index == '\0')
		return (NULL);

	while (*index != '\0')
	{
		for (i = 0; delim[i] != '\0'; i++)
		{
			if (*index == delim[i])
			{
				if (index == string)
				{
					index++;
					string++;
				}
				else
				{
					*index = '\0';
					break;
				}
			}
		}

		if (*index == '\0')
		{
			index++;
			return (string);
		}
		index++;
	}
	return (string);
}

