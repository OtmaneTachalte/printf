#include "main.h"

/**
 * print_char - Prints a char
 * @args: Argument list
 * @buf: Buffer array
 * @flags: Active flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_char(va_list args, char buf[], int flags, int width, int precision, int size)
{
	char character = va_arg(args, int);

	return (handle_write_char(character, buf, flags, width, precision, size));
}

/**
 * print_string - Prints a string
 * @args: Argument list
 * @buf: Buffer array
 * @flags: Active flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_string(va_list args, char buf[], int flags, int width, int precision, int size)
{
	int len = 0, idx;
	char *s = va_arg(args, char *);

	UNUSED(buf);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (!s)
	{
		s = "(null)";
		if (precision >= 6)
			s = "      ";
	}

	while (s[len])
		len++;

	if (precision >= 0 && precision < len)
		len = precision;

	if (width > len)
	{
		if (flags & F_MINUS)
		{
			write(1, &s[0], len);
			for (idx = width - len; idx > 0; idx--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (idx = width - len; idx > 0; idx--)
				write(1, " ", 1);
			write(1, &s[0], len);
			return (width);
		}
	}

	return (write(1, s, len));
}

/**
 * print_percent - Prints a percent sign
 * @args: Argument list
 * @buf: Buffer array
 * @flags: Active flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_percent(va_list args, char buf[], int flags, int width, int precision, int size)
{
	UNUSED(args);
	UNUSED(buf);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	return (write(1, "%%", 1));
}

/**
 * print_int - Prints an integer
 * @args: Argument list
 * @buf: Buffer array
 * @flags: Active flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_int(va_list args, char buf[], int flags, int width, int precision, int size)
{
	int idx = BUFF_SIZE - 2;
	int negative = 0;
	long int number = va_arg(args, long int);
	unsigned long int abs_num;

	number = convert_size_number(number, size);

	if (number == 0)
		buf[idx--] = '0';

	buf[BUFF_SIZE - 1] = '\0';
	abs_num = (unsigned long int)number;

	if (number < 0)
	{
		abs_num = (unsigned long int)(-number);
		negative = 1;
	}

	while (abs_num)
	{
		buf[idx--] = (abs_num % 10) + '0';
		abs_num /= 10;
	}

	idx++;

	return (write_number(negative, idx, buf, flags, width, precision, size));
}

/**
 * print_binary - Prints binary representation
 * @args: Argument list
 * @buf: Buffer array
 * @flags: Active flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_binary(va_list args, char buf[], int flags, int width, int precision, int size)
{
	unsigned int num, divisor, idx, sum;
	unsigned int binary[32];
	int count;

	UNUSED(buf);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	num = va_arg(args, unsigned int);
	divisor = 2147483648; /* (2 ^ 31) */
	binary[0] = num / divisor;

	for (idx = 1; idx < 32; idx++)
	{
		divisor /= 2;
		binary[idx] = (num / divisor) % 2;
	}

	for (idx = 0, sum = 0, count = 0; idx < 32; idx++)
	{
		sum += binary[idx];
		if (sum || idx == 31)
		{
			char digit = '0' + binary[idx];
			write(1, &digit, 1);
			count++;
		}
	}
	return (count);
}
