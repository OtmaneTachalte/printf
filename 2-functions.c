#include "main.h"

/**
 * print_pointer - Prints the value of a pointer variable
 * @args: Argument list
 * @buf: Buffer array
 * @flags: Active flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int print_pointer(va_list args, char buf[], int flags,
		int width, int precision, int size)
{
	char map[] = "0123456789abcdef";
	void *ptr;
	unsigned long ptr_value;
	int idx = BUFF_SIZE - 2, len = 2, padding_start = 1;
	char additional_char = 0, padding_char = ' ';

	(void)width;
	(void)size;
	(void)precision;

	ptr = va_arg(args, void *);

	if (ptr == NULL)
		return (write(1, "(nil)", 5));

	buf[BUFF_SIZE - 1] = '\0';
	ptr_value = (unsigned long)ptr;

	while (ptr_value)
	{
		buf[idx--] = map[ptr_value % 16];
		ptr_value /= 16;
		len++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padding_char = '0';
	if (flags & F_PLUS)
		additional_char = '+', len++;
	else if (flags & F_SPACE)
		additional_char = ' ', len++;

	idx++;

	return (write_pointer(buf, idx, len, width,
			flags, padding_char, additional_char, padding_start));
}

/**
 * print_non_printable - Prints ascii codes in hex of non-printable chars
 * @args: Argument list
 * @buf: Buffer array
 * @flags: Active flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_non_printable(va_list args, char buf[], int flags,
		int width, int precision, int size)
{
	char *str;
	int i = 0, off = 0;

	(void)flags;
	(void)width;
	(void)precision;
	(void)size;

	str = va_arg(args, char *);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[i])
	{
		if (is_printable(str[i]))
			buf[i + off] = str[i];
		else
			off += append_hexa_code(str[i], buf, i + off);
		i++;
	}

	buf[i + off] = '\0';

	return (write(1, buf, i + off));
}

/**
 * print_reverse - Prints reverse string
 * @args: Argument list
 * @buf: Buffer array
 * @flags: Active flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_reverse(va_list args, char buf[], int flags,
		int width, int precision, int size)
{
	char *str;
	int i, count = 0;

	(void)buf;
	(void)flags;
	(void)width;
	(void)precision;
	(void)size;

	str = va_arg(args, char *);

	if (str == NULL)
		str = ")Null(";

	for (i = 0; str[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		char z = str[i];
		write(1, &z, 1);
		count++;
	}
	return (count);
}

/**
 * print_rot13string - Prints a string in rot13
 * @args: Argument list
 * @buf: Buffer array
 * @flags: Active flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_rot13string(va_list args, char buf[], int flags,
		int width, int precision, int size)
{
	char input[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char output[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";
	char *str;
	unsigned int i, j;
	char ch;
	int count = 0;

	(void)buf;
	(void)flags;
	(void)width;
	(void)precision;
	(void)size;

	str = va_arg(args, char *);

	if (str == NULL)
		str = "(AHYY)";

	for (i = 0; str[i]; i++)
	{
		for (j = 0; input[j]; j++)
		{
			if (input[j] == str[i])
			{
				ch = output[j];
				write(1, &ch, 1);
				count++;
				break;
			}
		}
		if (!input[j])
		{
			ch = str[i];
			write(1, &ch, 1);
			count++;
		}
	}
	return (count);
}
