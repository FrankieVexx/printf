#include "main.h"

/************************* PRINT UNSIGNED NUMBER *************************/
/**
 * print_unsigned - Print unsigned number
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Find flags
 * @width: The width
 * @prec: The precision
 * @size: The size specifier
 * Return: The number of characters to be printed.
 */
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int prec, int size)
{
	int index = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[index--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[index--] = (num % 10) + '0';
		num /= 10;
	}

	index++;

	return (write_unsgnd(0, index, buffer, flags, width, prec, size));
}

/************* PRINT UNSIGNED NUMBER IN OCTAL  ****************/
/**
 * print_octal - Prints a  number in octal
 * @types: The list of arguments
 * @buffer: An array to handle print
 * @flags:  Find flags
 * @width: The width
 * @prec: The precision
 * @size: The size specifier
 * Return: The number of characters to be printed
 */
int print_octal(va_list types, char buffer[],
	int flags, int width, int prec, int size)
{

	int index = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[index--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[index--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[index--] = '0';

	index++;

	return (write_unsgnd(0, index, buffer, flags, width, prec, size));
}

/************** PRINT UNSIGNED NUMBER IN HEXADECIMAL **************/
/**
 * print_hexadecimal - Prints an unsigned number in hexadecimal notation
 * @types: The list of arguments
 * @buffer:an array to handle print
 * @flags:  Find active flags
 * @width: The width
 * @prec:  The precision
 * @size: The size
 * Return: The number of characters printed
 */
int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int prec, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, prec, size));
}

/************* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL **************/
/**
 * print_hexa_upper - Print unsigned number in upper hexadecimal
 * @types: The list of arguments
 * @buffer: an array to handle print
 * @flags:  Find flags
 * @width: The width
 * @prec: The precision
 * @size: The size specifier
 * Return: The number of characters printed
 */
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int prec, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, prec, size));
}

/************** PRINT HEXX NUMBER IN LOWER OR UPPER **************/
/**
 * print_hexa - Print a hexadecimal number in lowercase or uppercase
 * @types: The list of arguments
 * @map_to: an array of values to map the number to
 * @buffer: an array to handle print
 * @flags:  Find active flags
 * @flag_ch: Find flags
 * @width: The width
 * @prec: The precision specification
 * @size: The size specifier
 * @size: Size specification
 * Return: The number of characters printed
 */
int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int prec, int size)
{
	int index = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[index--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[index--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[index--] = flag_ch;
		buffer[index--] = '0';
	}

	index++;

	return (write_unsgnd(0, index, buffer, flags, width, prec, size));
}
