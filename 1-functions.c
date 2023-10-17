#include "main.h"

/**
 * print_unsigned - Prints an unsigned number
 * @args: Argument list
 * @buf: Buffer array
 * @flags: Active flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int print_unsigned(va_list args, char buf[], int flags,
	int width, int precision, int size)
{
	int idx = BUFF_SIZE - 2;
	unsigned long int number = va_arg(args, unsigned long int);

	number = convert_size_unsgnd(number, size);

	if (number == 0)
		buf[idx--] = '0';

	buf[BUFF_SIZE - 1] = '\0';

	while (number)
	{
		buf[idx--] = (number % 10) + '0';
		number /= 10;
	}

	idx++;

	return (write_unsgnd(0, idx, buf, flags, width, precision, size));
}

/**
 * print_octal - Prints a number in octal notation
 * @args: Argument list
 * @buf: Buffer array
 * @flags: Active flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_octal(va_list args, char buf[], int flags,
	int width, int precision, int size)
{
	int idx = BUFF_SIZE - 2;
	unsigned long int number = va_arg(args, unsigned long int);
	unsigned long int original_number = number;

	number = convert_size_unsgnd(number, size);

	if (number == 0)
		buf[idx--] = '0';

	buf[BUFF_SIZE - 1] = '\0';

	while (number)
	{
		buf[idx--] = (number % 8) + '0';
		number /= 8;
	}

	if (flags & F_HASH && original_number)
		buf[idx--] = '0';

	idx++;

	return (write_unsgnd(0, idx, buf, flags, width, precision, size));
}

/**
 * print_hexadecimal - Prints a number in lowercase hex
 * @args: Argument list
 * @buf: Buffer array
 * @flags: Active flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_hexadecimal(va_list args, char buf[], int flags,
	int width, int precision, int size)
{
	return (print_hexa(args, "0123456789abcdef", buf, flags,
		'x', width, precision, size));
}

/**
 * print_hexa_upper - Prints a number in uppercase hex
 * @args: Argument list
 * @buf: Buffer array
 * @flags: Active flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_hexa_upper(va_list args, char buf[], int flags,
	int width, int precision, int size)
{
	return (print_hexa(args, "0123456789ABCDEF", buf, flags,
		'X', width, precision, size));
}

/**
 * print_hexa - Prints hex in either lower or upper
 * @args: Argument list
 * @map: Array of chars to map the number to
 * @buf: Buffer array
 * @flags: Active flags
 * @flag_char: Flag char for case
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_hexa(va_list args, char map[], char buf[], int flags,
	char flag_char, int width, int precision, int size)
{
	int idx = BUFF_SIZE - 2;
	unsigned long int number = va_arg(args, unsigned long int);
	unsigned long int original_number = number;

	number = convert_size_unsgnd(number, size);

	if (number == 0)
		buf[idx--] = '0';

	buf[BUFF_SIZE - 1] = '\0';

	while (number)
	{
		buf[idx--] = map[number % 16];
		number /= 16;
	}

	if (flags & F_HASH && original_number)
	{
		buf[idx--] = flag_char;
		buf[idx--] = '0';
	}

	idx++;

	return (write_unsgnd(0, idx, buf, flags, width, precision, size));
}
