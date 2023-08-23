#include "main.h"
/**
 * line_reader - function that reads the user input string.
 * @end_of_file: return value of getline function
 *
 * Return: user input string.
 */
char *line_reader(int *end_of_file)
{
	size_t buffer_size;
	char *user_input = NULL;

	buffer_size = 0;

	*end_of_file = _getline(&user_input, &buffer_size, stdin);

	return (user_input);
}

/**
 * _getline - function that reads user input from stream.
 * @buffer: buffer that stores the user input characters.
 * @size: size of the buffer that stores the user input characters.
 * @stream: stream to read from which is (stdin).
 * Return: number of bytes, characters.
 */
ssize_t _getline(char **buffer, size_t *size, FILE *stream)
{
	char *strbuffer;
	char lastchar = 'z';
	static ssize_t usrinput;
	ssize_t retuvalue;
	int inpchar;

	if (usrinput == 0)
		fflush(stream);
	else
		return (-1);

	usrinput = 0;
	strbuffer = malloc(sizeof(char) * 1024);
	if (strbuffer == 0)
		return (-1);

	for (; lastchar != '\n';)
	{
		inpchar = read(STDIN_FILENO, &lastchar, 1);
		if (inpchar == -1 || (inpchar == 0 && usrinput == 0))
		{
			free(strbuffer);
			return (-1);
		}
		if (usrinput != 0 && inpchar == 0)
		{
			usrinput++;
			break;
		}
		if (usrinput >= 1024)
			strbuffer = _realloc(strbuffer, usrinput, usrinput + 1);
		strbuffer[usrinput] = lastchar;
		usrinput++;
	}
	strbuffer[usrinput] = '\0';
	_getline2(buffer, size, strbuffer, usrinput);
	retuvalue = usrinput;
	if (inpchar != 0)
		usrinput = 0;
	return (retuvalue);
}

/**
 * _getline2 - helper function for _getline(), that compares and assign
 * the result to it.
 * @bufferdp: buffer that store the user input string of characters.
 * @sizedp: size of user input line.
 * @strb: string of characters that is in the line.
 * @inpsize: size of the user input buffer.
 */
void _getline2(char **bufferdp, size_t *sizedp, char *strb, size_t inpsize)
{
	if (*sizedp < inpsize)
	{
		if (inpsize > 1024)
		{
			*sizedp = inpsize;
		}
		else
		{
			*sizedp = 1024;
		}
		*bufferdp = strb;
	}
	else if (*bufferdp == NULL)
	{
		if (inpsize > 1024)
		{
			*sizedp = inpsize;
		}
		else
		{
			*sizedp = 1024;
		}
		*bufferdp = strb;
	}
	else
	{
		_strcpy(*bufferdp, strb);
		free(strb);
	}
}

