#include "main.h"

/************************* PRINT CHAR *************************/

/**
 * print_char - Prints a character
 * @types: List the types of arguments
 * @buffer: An array that handles print
 * @flags:  Show available flags
 * @width: The width
 * @prec: The Precision to be specified
 * @size:  This is a size specifier
 * Return: The number of chars printed or NULL
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int prec, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, prec, size));
}
/************************* PRINT A STRING *************************/
/**
 * print_string - Prints a string
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @prec: The precision
 * @size: The size specifier
 * Return: The number of characters to be printed or NULL
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int prec, int size)
{
	int length = 0, index;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(prec);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (prec >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (prec >= 0 && prec < length)
		length = prec;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (index = width - length; index > 0; index--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (index = width - length; index > 0; index--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}
/************************* PRINT PERCENT SIGN *************************/
/**
 * print_percent - Prints a percent sign
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width:The width.
 * @prec: The precision
 * @size: The size of the specifier
 * Return: The number of characters printed
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int prec, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(prec);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/************************* PRINT INT *************************/
/**
 * print_int - Print int
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: The width.
 * @prec: The precision
 * @size: The size of the specifier
 * Return: The number of characters printed
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int prec, int size)
{
	int index = BUFF_SIZE - 2;
	int is_negative = 0;
	long int numb = va_arg(types, long int);
	unsigned long int num;

	numb = convert_size_number(numb, size);

	if (numb == 0)
		buffer[index--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)numb;

	if (numb < 0)
	{
		num = (unsigned long int)((-1) * numb);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[index--] = (num % 10) + '0';
		num /= 10;
	}

	index++;

	return (write_number(is_negative, index, buffer, flags, width, prec, size));
}

/************************* PRINT BINARY *************************/
/**
 * print_binary - Prints an unsigned number
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: The width.
 * @prec: The precision
 * @size: The size specifier
 * Return: The number of characters printed.
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int prec, int size)
{
	unsigned int n, m, index, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(prec);
	UNUSED(size);

	n = va_arg(types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	for (index = 1; index < 32; index++)
	{
		m /= 2;
		a[index] = (n / m) % 2;
	}
	for (index = 0, sum = 0, count = 0; index < 32; index++)
	{
		sum += a[index];
		if (sum || index == 31)
		{
			char z = '0' + a[index];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
