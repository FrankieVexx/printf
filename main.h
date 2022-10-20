#ifndef MAIN_H
#define MAIN_H

#include <limits.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

/* Macros for flag modifiers */

#define PLUS 1
#define SPACE 2
#define HASH 4
#define ZERO 8
#define NEG 16
#define PLUS_FLAG (flags & 1)
#define SPACE_FLAG ((flags >> 1) & 1)
#define HASH_FLAG ((flags >> 2) & 1)
#define ZERO_FLAG ((flags >> 3) & 1)
#define NEG_FLAG ((flags >> 4) & 1)

/* Length modifier Macros */

#define SHORT 1
#define LONG 2

/**
 * struct buffer_s - is a new type that defines a buffer struct
 * @buffer: a pointer to a character array
 * @start: a pointer to the beginning of a buffer
 * @len: the length of the string stored in the buffer
 */
typedef struct buffer_s
{
	char *buffer;
	char *start;
	unsigned int len;
} buffer_t;

/**
 * struct converter_s - A new type defining a converter struct
 * @specifier: A character representing a conversion specifier
 * @func: a pointer to a onversion function that corresponds to the specifier
 */
typedef struct conversion_s
{
	unsigned char specifier;
	unsinged int (*func)(va_list, buffer_t *, 
			unsigned char, int, unsigned char);
} converter_t;

/**
 * struct flag_s -  A new type defining a flags struct
 * @flag: a character representing a flag
 * @value: The int value of the given flag
 */
typedef struct flag_s
{
	unsigned char flag;
	unsigned char value;
} flag_t;

int _printf(const char *format, ....);
