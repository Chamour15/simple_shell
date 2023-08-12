#include "main.h"

/**
 * number_length - function that get the lenght of a number.
 * @num: int number.
 *
 * Return: the lenght of the number.
 */
int number_length(int num)
{
	int num_length = 1;
	unsigned int num1;

	if (num < 0)
	{
		num_length++;
		num1 = num * -1;
	}
	else
	{
		num1 = num;
	}

	while (num1 > 9)
	{
		num_length++;
		num1 = num1 / 10;
	}

	return (num_length);
}

/**
 * _strlen - function that get the lenght of a string.
 * @str: pointer to string of character.
 *
 * Return: the length of the string.
 */
int _strlen(const char *str)
{
	int str_len = 0;

	while (str[str_len] != 0)
	{
		str_len++;
	}

	return (str_len);
}

/**
 * _itoa - function that converts int to string.
 * @num: given number.
 *
 * Return: converted int to string.
 */
char *_itoa(int num)
{
	char *buffer;
	unsigned int num1;
	int num_length = number_length(num);

	buffer = malloc((num_length + 1) * sizeof(char));
	if (buffer == NULL)
	{
		return (NULL);
	}

	*(buffer + num_length) = 0;

	if (num < 0)
	{
		num1 = num * -1;
		buffer[0] = 45;
	}
	else
	{
		num1 = num;
	}

	num_length--;

	do {
		*(buffer + num_length) = (num1 % 10) + 48;
		num1 = num1 / 10;
		num_length--;
	} while (num1 > 0);

	return (buffer);
}

/**
 * _atoi - function that convert a string to an integer.
 * @s: string value.
 *
 * Return: integer value.
 */
int _atoi(char *s)
{
	unsigned int lenCount = 0, size = 0, i = 0, j = 1, k = 1, l;

	while (*(s + lenCount) != 0)
	{
		if (size > 0 && (*(s + lenCount) < 48 || *(s + lenCount) > 57))
		{
			break;
		}
		if (*(s + lenCount) == 45)
		{
			j *= -1;
		}
		if ((*(s + lenCount) >= 48) && (*(s + lenCount) <= 57))
		{
			if (size > 0)
			{
				k *= 10;
			}
			size++;
		}
		lenCount++;
	}

	for (l = lenCount - size; l < lenCount; l++)
	{
		i = i + ((*(s + l) - 48) * k);
		k /= 10;
	}

	return (i * j);
}

/**
 * _isdigit - function that checks for a digit (0 through 9).
 *@s: input string.
 *
 * Return: 1 if string is a number. 0 in other case.
 */
int _isdigit(const char *s)
{
	unsigned int i = 0;

	while (s[i])
	{
		if (s[i] < 48 || s[i] > 57)
		{
			return (0);
		}
		i++;
	}

	return (1);
}

