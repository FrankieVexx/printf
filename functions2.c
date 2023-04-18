#include "main.h"

/****************** PRINT POINTER ******************/
/**
 * print_pointer - Print the value of a pointer
 * @types: The list of arguments
 * @buffer: Buffer array to handle print
 * @flags: find flags
 * @width: the width
 * @prec: The precision
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int print_pointer(va_list types, char buffer[],
	int flags, int width, int prec, int size)
{
	char extra_c = 0, padd = ' ';
	int index = BUFF_SIZE - 2, length = 2, padd_start = 1; /* length'0x'=2 */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(prec);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buffer[index--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_c = '+', length++;
	else if (flags & F_SPACE)
		extra_c = ' ', length++;

	index++;

	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	return (write_pointer(buffer, index, length,
		width, flags, padd, extra_c, padd_start));
}

/************************* PRINT NON PRINTABLE *************************/
/**
 * print_non_printable - Print ascii codes
 * @types: The list of arguments
 * @buffer: an array to handle print
 * @flags:  find active flags
 * @width: the width
 * @prec: the precision
 * @size: The size specifier
 * Return: The number of characters printed
 */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int prec, int size)
{
	int index = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(prec);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[index] != '\0')
	{
		if (is_printable(str[index]))
			buffer[index + offset] = str[index];
		else
			offset += append_hexa_code(str[index], buffer, index + offset);

		index++;
	}

	buffer[index + offset] = '\0';

	return (write(1, buffer, index + offset));
}

/************************* PRINT REVERSE *************************/
/**
 * print_reverse - Prints reverse string.
 * @types: The list of arguments
 * @buffer: An array to handle print
 * @flags:  Find active flags
 * @width: The width
 * @prec: The Precision
 * @size: The size specifier
 * Return: The number of characters to be printed
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int prec, int size)
{
	char *str;
	int index, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(prec);

		str = ")Null(";
	}
	for (index = 0; str[index]; index++)
		;

	for (index = index - 1; index >= 0; index--)
	{
		char z = str[index];

		write(1, &z, 1);
		count++;
	}
	return (count);
}
/************************* PRINT A STRING IN ROT13 *************************/
/**
 * print_rot13string - Print a string in rot13.
 * @types: The list of arguments
 * @buffer: An array to handle print
 * @flags:  Find active flags
 * @width: The width
 * @prec: The precision
 * @size: The size of specifier
 * Return: The number of characters printed
 */
int print_rot13string(va_list types, char buffer[],
	int flags, int width, int prec, int size)
{
	char x;
	char *str;
	unsigned int index, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(prec);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (index = 0; str[index]; index++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[index])
			{
				x = out[j];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!in[j])
		{
			x = str[index];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}
