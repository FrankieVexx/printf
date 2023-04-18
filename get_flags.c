#include "main.h"

/**
 * get_flags - Gets all active flags
 * @format: A formatted string to print the arguments
 * @i: a parameter.
 * Return: Flags:
 */
int get_flags(const char *format, int *i)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int j, crt_i;
	int flags = 0;
	const char FLAGS_CHR[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARRY[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (crt_i = *i + 1; format[crt_i] != '\0'; crt_i++)
	{
		for (j = 0; FLAGS_CHR[j] != '\0'; j++)
			if (format[crt_i] == FLAGS_CHR[j])
			{
				flags |= FLAGS_ARRY[j];
				break;
			}

		if (FLAGS_CHR[j] == 0)
			break;
	}

	*i = crt_i - 1;

	return (flags);
}
