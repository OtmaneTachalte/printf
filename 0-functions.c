#include "main.h"

/**
 * print_char - Prints a character.
 * @types: List of arguments.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags.
 * @width: Width.
 * @precision: Precision specification.
 * @size: Size specifier.
 * Return: Number of characters printed.
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c;

	c = va_arg(types, int);
	return (handle_write_char(c, buffer, flags, width, precision, size));
}

/**
 * print_string - Prints a string.
 * @types: List of arguments.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags.
 * @width: Width.
 * @precision: Precision specification.
 * @size: Size specifier.
 * Return: Number of characters printed.
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, i;
	char *str;

	str = va_arg(types, char *);
	if (!str)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	for (length = 0; str[length]; length++)
		;
	if (precision >= 0 && precision < length)
		length = precision;
	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, str, length);
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		for (i = width - length; i > 0; i--)
			write(1, " ", 1);
	}
	return (write(1, str, length));
}

/**
 * print_percent - Prints a percent sign.
 * @types: List of arguments.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags.
 * @width: Width.
 * @precision: Precision specification.
 * @size: Size specifier.
 * Return: Number of characters printed.
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	(void)types;
	(void)buffer;
	(void)flags;
	(void)width;
	(void)precision;
	(void)size;
	return (write(1, "%", 1));
}

/**
 * print_int - Prints an integer.
 * @types: List of arguments.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags.
 * @width: Width.
 * @precision: Precision specification.
 * @size: Size specifier.
 * Return: Number of characters printed.
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n;
	unsigned long int num;

	n = va_arg(types, long int);
	num = (unsigned long int)n;
	if (n < 0)
	{
		num = (unsigned long int)(-1 * n);
		is_negative = 1;
	}
	while (num)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}
	i++;
	return (write_number(is_negative, i, buffer, flags, width, precision, size));
}

/**
 * print_binary - Prints a number in binary.
 * @types: List of arguments.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags.
 * @width: Width.
 * @precision: Precision specification.
 * @size: Size specifier.
 * Return: Number of characters printed.
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int n, m, i, sum, a[32];
	int count;

	n = va_arg(types, unsigned int);
	m = 2147483648;
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
