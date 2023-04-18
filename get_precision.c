#include "main.h"

/**
 * get_precision - Gets the precision for printing
 * @format: Formatted string in which to print the arguments
 * @i: The list of arguments to be printed.
 * @list: The list of arguments.
 *
 * Return: Precision.
 */
int get_precision(const char *format, int *i, va_list list)
{
	int crt_i = *i + 1;
	int precision = -1;

	if (format[crt_i] != '.')
		return (precision);

	precision = 0;

	for (crt_i += 1; format[crt_i] != '\0'; crt_i++)
	{
		if (is_digit(format[crt_i]))
		{
			precision *= 10;
			precision += format[crt_i] - '0';
		}
		else if (format[crt_i] == '*')
		{
			crt_i++;
			precision = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = crt_i - 1;

	return (precision);
}
