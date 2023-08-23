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
 * _strtok - function that tokenize a string by some delimiter.
 * @string: input string.
 * @delim: delimiter.
 *
 * Return: tokenized string.
 */
char *_strtok(char string[], const char *delim)
{
	unsigned int i, j;
	static char *strtotok, *strend;
	char *stri;

	if (string != NULL)
	{
		if (charcmp(string, delim))
			return (NULL);
		strtotok = string;
		i = _strlen(string);
		strend = &string[i];
	}
	stri = strtotok;
	if (stri == strend)
		return (NULL);
	for (j = 0; *strtotok; strtotok++)
	{
		if (strtotok != stri)
		{
			if (*strtotok && *(strtotok - 1) == '\0')
				break;
		}
		for (i = 0; delim[i]; i++)
		{
			if (*strtotok == delim[i])
			{
				*strtotok = '\0';
				if (strtotok == stri)
					stri++;
				break;
			}
		}
		if (*strtotok && j == 0)
			j = 1;
	}
	if (j == 0)
		return (NULL);
	return (stri);
}

