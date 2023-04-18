#include "main.h"

/**
 * get_width - Gets the width for printing
 * @format: The formatted string to print the arguments.
 * @i: The list of arguments to be printed.
 * @list: The list of arguments.
 *
 * Return: width.
 */
int get_width(const char *format, int *i, va_list list)
{
	int crt_i;
	int width = 0;

	for (crt_i = *i + 1; format[crt_i] != '\0'; crt_i++)
	{
		if (is_digit(format[crt_i]))
		{
			width *= 10;
			width += format[crt_i] - '0';
		}
		else if (format[crt_i] == '*')
		{
			crt_i++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = crt_i - 1;

	return (width);
}
