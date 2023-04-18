#include "main.h"

/**
 * get_size - gets the size to cast the argument
 * @format: The formatted string to print the arguments
 * @i: The list of arguments to be printed.
 *
 * Return: size.
 */
int get_size(const char *format, int *i)
{
	int crt_i = *i + 1;
	int size = 0;

	if (format[crt_i] == 'l')
		size = S_LONG;
	else if (format[crt_i] == 'h')
		size = S_SHORT;

	if (size == 0)
		*i = crt_i - 1;
	else
		*i = crt_i;

	return (size);
}
