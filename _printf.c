#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Printf function that prints out given output
 * @format: format of the printed item
 * Return: Printed chars.
 */
int _printf(const char *format, ...)
{
	int index, printed = 0, printed_chars = 0;
	int flags, width, prec, size, buff_ind = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);
	/*iterate through the indices */
	for (index = 0; format && format[index] != '\0'; index++)
	{
		if (format[index] != '%')
		{
			buffer[buff_ind++] = f[index];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			/* write(1, &f[index], 1);*/
			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flags = get_flags(format, &index);
			width = get_width(format, &index, list);
			prec = get_precision(format, &index, list);
			size = get_size(format, &index);
			++index;
			printed = handle_print(format, &index, list, buffer,
				flags, width, prec, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}

	print_buffer(buffer, &buff_ind);

	va_end(list);

	return (printed_chars);
}

/**
 * print_buffer - Prints the contents of the buffer if it exists or NULL if not
 * @buffer: An Array of characters to be printed
 * @buff_ind: Index at which to add next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}
